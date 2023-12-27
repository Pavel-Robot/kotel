#define UART_SIM800 & huart3
//#define FREERTOS 1
#define CMD_DELAY 2000

#include "main.h"

extern UART_HandleTypeDef huart3;


uint8_t rx_data = 0;
uint8_t rx_buffer[32] = {0};

uint8_t rx_index = 0; //По сути длина принятая до \r\n
char answer[32] = {0}; //Ответ на АТ команды

//uint8_t flag_counter_RX = 0; //Флаг учитывать кол-ва \r\n или нет
//uint8_t counter_RX_RN = 0; //счетчик сколько раз мы встретили \r\n в ответе АТ команд
uint8_t info_buffer[32] = {0};
uint8_t info_index = 0;

void Sim800_RxCallBack(void);


uint8_t SIM800_SendCommand(char *command, char *reply, uint16_t delay);

uint8_t SIM800_Init(void);

uint8_t StatsD_Connect(char *apn, char *apn_user, char *apn_pass, char *host, uint16_t port);

uint8_t StatsD_SendInt(char *metric, uint32_t value, char *type);

uint8_t StatsD_SendDouble(char *metric, double value, char *type);




/**
  * Call back function for release read SIM800 UART buffer.
  * @param NONE
  * @return SIM800 answer for command (char answer[64])
*/
void Sim800_RxCallBack(void) {
    rx_buffer[rx_index++] = rx_data;
    info_buffer[info_index++] = rx_data;

    if (strstr((char *) rx_buffer, "\r\n") != NULL && rx_index == 2) {
    	rx_index = 0;
    } else if (strstr((char *) rx_buffer, "\r\n") != NULL) {
        memcpy(answer, rx_buffer, sizeof(rx_buffer));
        rx_index = 0;
        memset(rx_buffer, 0, sizeof(rx_buffer));
    }
    HAL_UART_Receive_IT(UART_SIM800, &rx_data, 1);
}

//void Sim800_RxCallBack(void) { //+
//    rx_buffer[rx_index++] = rx_data;
//
//    if (strstr((char *) rx_buffer, "\r\n") != NULL && rx_index == 2) {
//    	rx_index = 0;
//    } else if (strstr((char *) rx_buffer, "\r\n") != NULL) {
//        memcpy(answer, rx_buffer, sizeof(rx_buffer));
//        rx_index = 0;
//        memset(rx_buffer, 0, sizeof(rx_buffer));
//    }
//    HAL_UART_Receive_IT(UART_SIM800, &rx_data, 1);
//}

/**
  * Send AT command to SIM800 over UART.
  * @param command the command to be used the send AT command
  * @param reply to be used to set the correct answer to the command
  * @param delay to be used to the set pause to the reply
  * @return error, 0 is OK
  */
//Отправляем команду, как показано в функции SIM800_SendData
uint8_t SIM800_SendCommand(char *command, char *reply, uint16_t delay) {

	//отправим АТ команду
	HAL_UART_Transmit_IT(UART_SIM800, (unsigned char *) command, (uint16_t) strlen(command));

    osDelay(delay); //подождем

    //если в ответе answer есть reply  (возврат strstr равен 1)
    if (strstr(answer, reply) != NULL) {
        rx_index = 0;
        //то заполнить rx_buffer нулями
        memset(rx_buffer, 0, sizeof(rx_buffer));

        return 0;  //успешное выполнение команды
    }
    rx_index = 0;
    memset(rx_buffer, 0, sizeof(rx_buffer));
    return 1;
}

/**
  * Send data over AT command.
  * @param buf the buffer into which the data will be send
  * @param len the length in bytes of the supplied buffer
  * @return error, 0 is OK
  */
//int SIM800_SendData(uint8_t *buf, int len) {
//    char str[32] = {0};
//    sprintf(str, "AT+CIPSEND=%d\r\n", len); //создать сообщение из str согласно второму аргументу
//    SIM800_SendCommand(str, "", 200); //Отправляем АТ команду, второй аргумент оставляем пустой строкой
//    HAL_UART_Transmit_IT(UART_SIM800, buf, len);
//
//    osDelay(200);
//
//    if (strstr(answer, "SEND OK") != NULL) {
//        rx_index = 0;
//        memset(rx_buffer, 0, sizeof(rx_buffer));
//        return 0;
//    }
//    rx_index = 0;
//    memset(rx_buffer, 0, sizeof(rx_buffer));
//    return 1;
//}

/**
  * initialization SIM800.
  * @param NONE
  * @return error the number of mistakes, 0 is OK
  */
uint8_t SIM800_Init(void) {
    uint8_t error = 0;

    HAL_UART_Receive_IT(UART_SIM800, &rx_data, 1);


    //Инициализация, если есть ошибка на команду, то error будет больше нуля
    error += SIM800_SendCommand("AT\r\n", "OK\r\n", CMD_DELAY); //Работает ли модуль sim800?
    error += SIM800_SendCommand("ATE0\r\n", "OK\r\n", CMD_DELAY); //

    //мое экспериметнальное
    //error += SIM800_SendCommand("AT+GMM\r\n", "SIMCOM_SIM800L\r\n", CMD_DELAY); //Индефикатор модуля

    //SIM800_SendCommand("AT+GSN\r\n", "", CMD_DELAY); //imei модуля получаем


    //error += SIM800_SendCommand("AT+CBC\r\n", "+CBC: 0,61,3895\r\n", CMD_DELAY); //Напряжение на модуле
//    error += SIM800_SendCommand("AT+CSQ\r\n", "SIMCOM_SIM800L\r\n", CMD_DELAY); //Индефикатор модуля

    return error;
}


//Функция постоянно мониторит уровень сигнала
uint8_t Sim800_Get_Signal(){

	char pow_char; //переменная для хранения уровня связи
	uint8_t pow_int = 0;

	info_index = 0; //обнуляем индекс

	SIM800_SendCommand("AT+CSQ\r\n", "", CMD_DELAY); //Первый параметр ответа - мощность сигнала rssi (от 10 и выше — нормальная):Второй параметр ответа - частота ошибок по битам ber:
	//+CSQ: 16,0\r\n


	//Тут нужно отпарсить сообщение, получив значение после +CSQ: (x), 0 и перевести его в int из строки
	pow_char = info_buffer[8];

	//pow_int = pow_char;
	//pow_int = sscanf(pow_char, "%d",  &pow_int);

	return pow_int;
}

//переводит инт из Sim800_Get_Signal в децибелы
int8_t decibel(uint8_t pow_int){

	return -113+2*pow_int;

}

int8_t Pow_Level(int8_t decibel){

	uint8_t flag = 0;

	if( decibel >= -70 ) flag = 0; //отличный - сильный сигнал, максимальная скорость передачи данных
	else if( decibel <= -70 && decibel >= -85 ) flag = 1; //Хороший сигнал, с быстрой скоростью передачи данных

}


//инициализация приема звонков
uint8_t Sim800_Get_Call(){

	uint8_t error = 0;

	error += SIM800_SendCommand("AT+CSMINS?\r\n", "+CSMINS: 0,1\r\n", CMD_DELAY); //Проверить обнаружение SIM-карты. Второй параметр в ответе должен быть 1. Если 0, значит карта не вставлена.

	error += SIM800_SendCommand("AT+COPS?\r\n", "+COPS:0,0,", CMD_DELAY); //Узнаем нашего оператора	+COPS:0,0,"Megafon"

	error += SIM800_SendCommand("AT+CCALR?\r\n", "OK\r\n", CMD_DELAY); //Готовность модуля совершать звонки

	error += SIM800_SendCommand("AT+CLIP=1\r\n", "RING\r\n", CMD_DELAY); // Включить определение номера

	return error;
}


////структура с информацией о модуле
//typedef struct SIM800INFO{
//
//	char imei[16];
//	char revision[30];
//
//
//} SIM800INFO;
//
//SIM800INFO sim800_info;
//
////Получение IMEI кода модуля
//void SIM800_GET_IMEI_Revision_(){
//
//	SIM800_SendCommand("AT+GSN\r\n", "", CMD_DELAY); //imei модуля получаем
//	memcpy(sim800_info.imei, answer, sizeof(answer));
//
//	osDelay(150);
//
//	SIM800_SendCommand("AT+GMR\r\n", "", CMD_DELAY); //Ревизия модуля получаем
//	memcpy(sim800_info.imei, answer, sizeof(answer));
//
//	osDelay(150);
//
//
//}

/**
  * Connect to StatsD server in Internet over UDP.
  * @param apn to be used the set APN for you GSM net
  * @param apn_user to be used the set user name for APN
  * @param apn_pass to be used the set password for APN
  * @param host to be used the set StatsD server IP or host name
  * @param port to be used the set StatsD server UDP port
  * @return error the number of mistakes, 0 is OK
  */
//int StatsD_Connect(char *apn, char *apn_user, char *apn_pass, char *host, uint16_t port) {
//    int error = 0;
//    char str[64] = {0};
//
//    error += SIM800_SendCommand("AT+CIPSHUT\r\n", "SHUT OK\r\n", CMD_DELAY);
//    error += SIM800_SendCommand("AT+CGATT=1\r\n", "OK\r\n", CMD_DELAY);
//
//    snprintf(str, sizeof(str), "AT+CSTT=\"%s\",\"%s\",\"%s\"\r\n", apn, apn_user, apn_pass);
//    error += SIM800_SendCommand(str, "OK\r\n", CMD_DELAY);
//
//    error += SIM800_SendCommand("AT+CIICR\r\n", "OK\r\n", CMD_DELAY);
//    SIM800_SendCommand("AT+CIFSR\r\n", "OK\r\n", CMD_DELAY);
//
//    memset(str, 0, sizeof(str));
//    sprintf(str, "AT+CIPSTART=\"UDP\",\"%s\",%d\r\n", host, port);
//    error += SIM800_SendCommand(str, "CONNECT OK\r\n", CMD_DELAY);
//
//    return error;
//}
//
///**
//  * Send on the StatsD server of the metric
//  * @param metric to be used to the set metric name
//  * @param value to be used to the set value for metric
//  * @param value to be used to the set type for metric
//  * @return error the number of mistakes, 0 is OK
//  */
//int StatsD_SendInt(char *metric, uint32_t value, char *type) {
//    int error = 0;
//    char buf[256] = {0};
//    sprintf(buf, "%s:%lu|%s", metric, value, type);
//    error += SIM800_SendData((unsigned char *) buf, (int) strlen(buf));
//    return error;
//}

//int StatsD_SendDouble(char *metric, double value, char *type) {
//    int error = 0;
//    char buf[256] = {0};
//    sprintf(buf, "%s:%f|%s", metric, value, type);
//    error += SIM800_SendData((unsigned char *) buf, (int) strlen(buf));
//    return error;
//}



/**
* @brief Function implementing the Task_SMS thread.
* @param argument: Not used
* @retval None
*/
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
          if(huart == &huart3)
          {
        	  Sim800_RxCallBack();
          }
}
