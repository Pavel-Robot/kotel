/*
 * ADC.h
 *
 *  Created on: Aug 31, 2022
 *      Author: user
 */

#ifndef SRC_APP_SENS_AND_ALL_H_
#define SRC_APP_SENS_AND_ALL_H_

#include <math.h>
#include "../Control/buttons_states.h"
//volatile

extern ADC_HandleTypeDef hadc1;
extern TIM_HandleTypeDef htim4;
extern uint8_t short_clicking;
extern TIM_HandleTypeDef htim3;

#define ADC_CHANNELS_NUM 6 //количество каналов для снятия напряжения посредством АЦП
#define REFERENCE_VOLTAGE 3.3 // Опорное напряжение (напряжение питания - можно корректировать)
#define SIZE_AVERAGE 10 //число измерений по которому высчитывается среднее для ацп

#define SENSITY_ACS712 185 //Чувствительность AC712 mV/A
#define SENSITY_UNIT_CURRENT 229 //кол-во единиц измерения АЦП для тока (185*4096/3300) SENSITY_ACS712*4096/REFERENCE_VOLTAGE
#define VALUE_ZERO_ACS_VOLTAGE 1.128 //Значение нуля отсчета тока (значение в вольтах 3.3/2) -Андрей говорит 1.5в, по мое значение 1.15


#define RELAY_DELAY_ONOFF 0 //Если 0, то задержки при переключении реле нет

#define TIME_BUTTON_SHORT 300 //время в мс, короткое нажатие
#define TIME_BUTTON_LONG 700 //время в мс, длинное нажатие




////коэффициенты для перевода из попугаев для аналоговых портов
//#define Temp_Boiler_Koeff 1
//#define Current_LM321_Koeff 1
//#define Temp_Screw_Koeff 1
//#define Temp_Gase_Koeff 1
//#define Temp_Water_Koeff 1
//#define Temp_Street_Koeff 1
////#define Hopper_Cover_Koeff 1
//#define Thermostat_Koeff 1
//#define Temp_STM32_Koeff 1
//#define STM32_Koeff_T 20

#define RESIST_DEV 10000 //Значение сопротивления одного резистора в делителе из резисторов (ом)




//#define ENC_A() HAL_GPIO_ReadPin(Encode_1_GPIO_Port, Encode_1_Pin) //енкодер
//#define ENC_B() HAL_GPIO_ReadPin(Encode_2_GPIO_Port, Encode_2_Pin) //енкодер
//#define ENC_DELAY 10
//uint8_t enc_a=0, enc_b=0, count_a=0, count_b=0; //енкодер
//uint8_t ab=0, encoder_state=0; //енкодер


float GetTempPT100(uint16_t Voltage);
//float Get_Resist(uint16_t Voltage);
float Get_Resist(uint16_t Voltage, uint16_t Resist_dev);
float Get_Current_Engine(uint16_t ACS_Voltage);
uint8_t Hopper_Cover_State();
uint8_t Thermostat_State();
void Pumps_Сentral_Heating(uint8_t flag);
void Pumps_Water_Supply(uint8_t flag);
//HAL_GPIO_EXTI_Callback; //ШИМ Вентилятора
void Blowdown(uint8_t work_time_sec, uint8_t not_work_time_sec); // продувка вентилятором (только в режиме поддержки)

void Time_Fl();
void Time_Emp();
void Time_Fuel_Combustion();
uint8_t Percent_Combustion(uint32_t Time_Combustion); //функция возвращающая процент оставшегося топлива


float Get_Temp_NTC3435(uint16_t R); //T(R) = -0.0073751 * R + 91.05

//void encode_defense_noise(); //дребезг енкодера
//void encode_turn();// Код для отслеживания поворота энкодера.


uint8_t rot_get_state();
//#define ENC_A() HAL_GPIO_ReadPin(Encoder_1_GPIO_Port, Encoder_1_Pin) //состояние енкодера на пине 1
//#define ENC_B() HAL_GPIO_ReadPin(Encoder_2_GPIO_Port, Encoder_2_Pin) // состояние енкодера на пине 2
//void encode();

//void UART_IT_Console(str message, Sens_a.Temp_Water){
//
//	uint8_t str[100];
//
//	sprintf(str, "Напряжение %d: %d\n ", 4, Sens_a.Temp_Water);
//
//	HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));
//
//}


//Глобальные переменные
uint16_t adcData[ADC_CHANNELS_NUM]; //В буфере adcData[] будем сохранять сырые данные с АЦП
uint32_t adcVoltage[ADC_CHANNELS_NUM]; //пересчитанные в миллиВольты значения
uint8_t flag_pwm_fan = 0; //Флаг, работает ли вентилятор в данный момент

uint32_t Time_Full; //Время, когда бак полон
uint32_t Time_Empty; //Время, когда бак пуст
uint32_t Time_Combustion; //Время сгорания топлива
//float Resist;
//float Temperature;

//uint8_t ProblemUart[100]; //Массив для UART
typedef struct{

	uint16_t voltage; //напряжение на канале АЦП (милливольты)
	uint16_t value; //значение параметра для выбранного устройства
	uint8_t state; //состояние датчика 0 -не подключен (напряжение 3.3в), 1 - подключен (напряжение между 3.3 и 0), 2 - короткое замыкание (напряжение 0)

} Parameters;
Parameters state_arr[ADC_CHANNELS_NUM];

//enum Who_I {
//	Temp_Boiler,
//	Current_LM321,
//	Temp_Screw,
//	Temp_Gase,
//	Temp_Water,
//	Temp_Street,
//	Hopper_Cover,
//	Thermostat
//};


//struct Sens_Analog {
//
//	uint16_t Temp_Boiler; //Температура котла
//	uint16_t Current_LM321; //Ток с LM321
//	uint16_t Temp_Screw; //Температура шнека
//	uint16_t Temp_Gase; //Температура дымовых газов
//	uint16_t Temp_Water; //Температура ГВС
//	uint16_t Temp_Street; //Температура улица
//	uint16_t Hopper_Cover; //Крышка бункера
//	uint8_t Thermostat; //Термостат
//	//int16_t Temp_STM32; //Температура с датчика температуры stm32
//	//int16_t Voltage_STM32; //Напряжение питания stm32
//};
//
//struct Sens_Analog Sens_a;

struct Sens_Analog {

	Parameters Temp_Boiler; //Температура котла
	Parameters Current_LM321; //Ток с LM321
	Parameters Temp_Screw; //Температура шнека
	Parameters Temp_Gase; //Температура дымовых газов
	Parameters Temp_Water; //Температура ГВС
	Parameters Temp_Street; //Температура улица
	Parameters Hopper_Cover; //Крышка бункера
	Parameters Thermostat; //Термостат
	//int16_t Temp_STM32; //Температура с датчика температуры stm32
	//int16_t Voltage_STM32; //Напряжение питания stm32
};

struct Sens_Analog Sens_a;




//Average_Get_Value_mVolt(&hadc1, adcData,  adcVoltage, ADC_CHANNELS_NUM);
void Average_Get_Value_mVolt(){

	uint32_t Bf[ADC_CHANNELS_NUM] = {0};

	//битовые значения
	for(uint8_t i = 0; i < SIZE_AVERAGE; i++){ // SIZE_AVERAGE Сколько измерений проводим

		//HAL_ADC_Init(&hadc1);
		HAL_ADC_Start_DMA(&hadc1, (uint32_t*) adcData, ADC_CHANNELS_NUM);  //измеряем напряжение АЦПшкой
		//osDelay(13);
		//HAL_ADC_Stop_DMA(&hadc1);
		//HAL_ADC_DeInit(&hadc1);
		//HAL_Delay(1);

		for(uint8_t j = 0; j < ADC_CHANNELS_NUM; j++){ //суммируем
			Bf[j] =  Bf[j] + adcData[j];
		}

	}
	//битовые значения

	//переводим в милливольты
	for (uint8_t i = 0; i < ADC_CHANNELS_NUM; i++){
		   adcVoltage[i] = (uint32_t) (1000*Bf[i] * REFERENCE_VOLTAGE / 4095); //в милливольты пересчитываем
		}


	//заполняем структуру, берем среднее
	Sens_a.Temp_Boiler.voltage = Get_Resist(adcVoltage[5]/SIZE_AVERAGE, 10000);
	Sens_a.Temp_Boiler.value = Get_Temp_NTC3435(Get_Resist(adcVoltage[5]/SIZE_AVERAGE, 10000)); //Температура котла
	//state_arr[0].state = Sens_a.Temp_Boiler.state;
	//state_arr[0].voltage = Sens_a.Temp_Boiler.voltage;

	Sens_a.Current_LM321.voltage = adcVoltage[1]/SIZE_AVERAGE;
	Sens_a.Current_LM321.value = Get_Current_Engine(Sens_a.Current_LM321.voltage); //Ток с LM321

//	Sens_a.Temp_Screw.voltage = adcVoltage[2]/SIZE_AVERAGE;
//	Sens_a.Temp_Screw.value = GetTempPT100(Sens_a.Temp_Screw.voltage); //Температура шнека
//	state_arr[1].state = Sens_a.Temp_Screw.state;
//	state_arr[1].voltage = Sens_a.Temp_Screw.voltage;
//
//	Sens_a.Temp_Gase.voltage = adcVoltage[3]/SIZE_AVERAGE;
//	Sens_a.Temp_Gase.value = GetTempPT100(Sens_a.Temp_Gase.voltage); //Температура дымовых газов
//	state_arr[2].state = Sens_a.Temp_Gase.state;
//	state_arr[2].voltage = Sens_a.Temp_Gase.voltage;
//
//	Sens_a.Temp_Water.voltage = adcVoltage[4]/SIZE_AVERAGE;
//	Sens_a.Temp_Water.value = GetTempPT100(Sens_a.Temp_Water.voltage); //Температура ГВС
//	state_arr[3].state = Sens_a.Temp_Water.state;
//	state_arr[3].voltage = Sens_a.Temp_Water.voltage;

	//Sens_a.Temp_Street.voltage = adcVoltage[5]/SIZE_AVERAGE;
	//Sens_a.Temp_Street.value = GetTempPT100(Sens_a.Temp_Street.voltage); //Температура улица
	//state_arr[4].state = Sens_a.Temp_Street.state;
	//state_arr[4].voltage = Sens_a.Temp_Street.voltage;

	//Sens_a.Hopper_Cover.voltage = Get_Resist(adcVoltage[5]/SIZE_AVERAGE, 1000) ; //не считываем напряжение с крышки, только уровень
	//Sens_a.Hopper_Cover.value = Get_Temp_NTC3435(Get_Resist(adcVoltage[5]/SIZE_AVERAGE, 1000)); //Крышка бункера - открыта или нет

	Sens_a.Thermostat.voltage = 0; //не считываем напряжение с крышки, только уровень
	Sens_a.Thermostat.value = Thermostat_State(); //Термостат
	state_arr[5].state = Sens_a.Thermostat.state;
	state_arr[5].voltage = Sens_a.Thermostat.voltage;

//	Sens_a.Temp_Boiler = GetTempPT100(adcVoltage[0]/SIZE_AVERAGE) * Temp_Boiler_Koeff; //Температура котла
//	Sens_a.Current_LM321 = Get_Current_Engine(adcVoltage[1]/SIZE_AVERAGE) * Current_LM321_Koeff; //Ток с LM321
//	Sens_a.Temp_Screw = GetTempPT100(adcVoltage[2]/SIZE_AVERAGE) * Temp_Screw_Koeff; //Температура шнека
//	Sens_a.Temp_Gase = GetTempPT100(adcVoltage[3]/SIZE_AVERAGE) * Temp_Gase_Koeff; //Температура дымовых газов
//	Sens_a.Temp_Water = GetTempPT100(adcVoltage[4]/SIZE_AVERAGE) * Temp_Water_Koeff; //Температура ГВС
//	Sens_a.Temp_Street = GetTempPT100(adcVoltage[5]/SIZE_AVERAGE) * Temp_Street_Koeff; //Температура улица
//	Sens_a.Hopper_Cover = Hopper_Cover_State(); //Крышка бункера - открыта или нет
//	Sens_a.Thermostat = adcVoltage[6]/SIZE_AVERAGE * Thermostat_Koeff; //Термостат

	//Sens_a.Temp_STM32 = Get_Temp_STM32(adcVoltage[7]/SIZE_AVERAGE) * Temp_STM32_Koeff; //Температура с датчика температуры stm32
}
//	Resist = (((float) Sens_a.Temp_Boiler/1000) * 10000) / ( (float) REFERENCE_VOLTAGE - ((float)Sens_a.Temp_Boiler/1000) );
//
//	float Rt = Resist/10;
//	//Temperature = 3383.8098-8658.0088*sqrt(0.1758481-0.000231*Rt); //Для PT100 от 0 до 850 градусов
//
//	float A, B, R0;
//	R0 = 1000;
//	A = 3.9083*pow(10, -3);
//	B = -5.775*pow(10, -7);
//	Temperature = (sqrt(A*A-4*B*(1-Rt/R0)) - A)/(2*B); //Для PT1000 от 0 до 850 градусов




//Для делителя обычного
//Получить сопротивление термопары, на вход функции подается напряжение измеренное на порту стм и сопротивление резисторa1 (ом), на выходе сопротивление термопары R2
//float Get_Temp_PT1000(uint16_t Voltage, uint16_t R1){
//
//	//uint16_t Resist;
//	float Rt, Temperature; //сопротивление и температура
//	float A, B, R0; //коэффициенты для рассчета
//
//	//получаем сопротивление датчика
//	Rt =  Get_Resist_PT(Voltage, R1);
//
//	R0 = 1000; //у датчика в даташите должно быть значение. Значение сопротивления при нулевой температуре
//	A = 3.9083*pow(10, -3);
//	B = -5.775*pow(10, -7);
//
//	Temperature = (sqrt(A*A-4*B*(1-Rt/R0)) - A)/(2*B); //Для PT1000 от 0 до 850 градусов
//
//
//	return Temperature;
//
//}


//Для делителя обычного
//Получить сопротивление термопары, на вход функции подается напряжение измеренное на порту стм и сопротивление резисторa1 (ом), на выходе сопротивление термопары R2
float GetTempPT100(uint16_t Voltage){
	//uint16_t Resist;
	float Rt, Temperature; //сопротивление и температура

	//получаем сопротивление датчика
	Rt = Get_Resist(Voltage, 10000);

	Temperature = 3383.8098-8658.0088*sqrt(0.1758481-0.000231*Rt); //Для PT100 от -200 до 850 градусов

	return Temperature;

}


////Для делителя обычного
////Функция получения сопротивления термопары
//float Get_Resist(uint16_t Voltage){
//
//	float Resist;
//	float U_diod = 0.0; //параметр учета падения напряжения на диоде (стабилитроне) + нужно добавить в формулу ниже
//
//	Resist = (((float) Voltage/1000) * RESIST_DEV) / ( (float) REFERENCE_VOLTAGE - ((float) Voltage/1000) ); //Для сопротивления 100 напряжение 0.035, для 10ком напряжение 1.6
//
//	return Resist;
//}

//Для делителя обычного
//Функция получения сопротивления термопары
float Get_Resist(uint16_t Voltage, uint16_t Resist_dev){

	float Resist;
	//float U_diod = 0.0; //параметр учета падения напряжения на диоде (стабилитроне) + нужно добавить в формулу ниже

	Resist = (((float) Voltage/1000) * Resist_dev) / ( (float) REFERENCE_VOLTAGE - ((float) Voltage/1000) ); //Для сопротивления 100 напряжение 0.035, для 10ком напряжение 1.6

	return Resist;
}


//Функция принимающая на вход напряжение (мВ) с ACS712 и возвращающая значение тока (мА)
float Get_Current_Engine(uint16_t ACS_Voltage){

	float Current;

	//Возможно стоит проводить калибровку без нагрузки для значения VALUE_ZERO_ACS_VOLTAGE
	Current = (VALUE_ZERO_ACS_VOLTAGE - ((float) ACS_Voltage/1000))/(SENSITY_UNIT_CURRENT*1000);

	return Current;
}


//Функция проверяющая состояние крышки бункера (0 - закрыта, 1 - открыта)
//uint8_t Hopper_Cover_State(){
//
//	//HAL_GPIO_WritePin(GPIOA, Hopper_Cover_PA6_Pin, flag); //if flag == 1 открыть, 0 -закрыть
//	//HAL_GPIO_ReadPin(GPIOx, GPIO_Pin);
//	uint8_t flag = HAL_GPIO_ReadPin(Hopper_Cover_GPIO_Port, Hopper_Cover_Pin);;
//
//	return flag;
//}


//	Выключаем/включаем насос центрального отопления (ЦО) 0-on, 1-off
void Pumps_Сentral_Heating(uint8_t flag){

	HAL_GPIO_WritePin(U6_MOC3021M_GPIO_Port, U6_MOC3021M_Pin, flag);
}


//Выключаем/включаем насос горячего водоснабжения (ГВС) 0-on, 1-off
void Pumps_Water_Supply(uint8_t flag){

	HAL_GPIO_WritePin(U7_MOC3021M_GPIO_Port, U7_MOC3021M_Pin, flag);
}







uint8_t rot_old_state = 0, rot_new_state = 0;
int8_t rot_cnt = 0;
uint16_t encode_val = 0;

uint8_t NewState = 0, OldState = 0, Vol = 0, upState = 0,downState = 0;

uint8_t rot_get_state() {
	return (uint8_t)((HAL_GPIO_ReadPin(Encoder_1_GPIO_Port, Encoder_1_Pin) << 1)
			| (HAL_GPIO_ReadPin(Encoder_2_GPIO_Port, Encoder_2_Pin)));
}

//ШИМ вентилятора
//5_MOC3021M_PB8 - TIM4 C3
//сравнение равно 5000, это значит, что когда сработает внешнее прерывание HAL_GPIO_EXTI_Callback
//и будет запущен таймер, он досчитает до 5000 и выдаст высокий уровень —
//симистор откроется. Далее таймер досчитает до 9000 и остановится.
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){ //Вызывается, когда на пине PB9 есть сигнал с PC817
	if (GPIO_Pin == U2_PC817_Pin) {
    HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_3);
    if( flag_pwm_fan == 1 ){ //для вкл/выкл вентилятора
    HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_3); //Таймер считает до значения value в  Set_PWM_ZC и отправляет импульс до времени 9000
    }
	}


    if (GPIO_Pin == Encoder_1_Pin || GPIO_Pin == Encoder_2_Pin) {


		rot_new_state = rot_get_state();

		// Check transition
		if (rot_old_state == 3 && rot_new_state == 2) {        // 3 -> 2 transition
			rot_cnt++;
		} else if (rot_old_state == 2 && rot_new_state == 0) { // 2 -> 0 transition
			rot_cnt++;
		} else if (rot_old_state == 0 && rot_new_state == 1) { // 0 -> 1 transition
			rot_cnt++;
		} else if (rot_old_state == 1 && rot_new_state == 3) { // 1 -> 3 transition
			rot_cnt++;
		} else if (rot_old_state == 3 && rot_new_state == 1) { // 3 -> 1 transition
			rot_cnt--;
		} else if (rot_old_state == 1 && rot_new_state == 0) { // 1 -> 0 transition
			rot_cnt--;
		} else if (rot_old_state == 0 && rot_new_state == 2) { // 0 -> 2 transition
			rot_cnt--;
		} else if (rot_old_state == 2 && rot_new_state == 3) { // 2 -> 3 transition
			rot_cnt--;
		} else{

			if(button_mail.mail_state == BUTTON_MAIL_PROCESSED){

				button_mail.mail_state = BUTTON_MAIL_UPDATED;
				button_mail.button_type = BUTTON_LEFT;
				button_mail.button_state = BUTTON_UP;

			}

			if(button_mail.mail_state == BUTTON_MAIL_PROCESSED){

				button_mail.mail_state = BUTTON_MAIL_UPDATED;
				button_mail.button_type = BUTTON_RIGHT;
				button_mail.button_state = BUTTON_UP;

			}


		}

//    	if(rot_cnt > 100) rot_cnt = 100;
//    	if(rot_cnt < 1) rot_cnt = 1;

    	rot_old_state = rot_new_state;

    	if (rot_cnt < 0){

    		if(button_mail.mail_state == BUTTON_MAIL_PROCESSED){

    			button_mail.mail_state = BUTTON_MAIL_UPDATED;
    			button_mail.button_type = BUTTON_LEFT;
    			button_mail.button_state = BUTTON_SHORT_PUSHED;

    		}
    	}

    	if(rot_cnt > 0){

    		if(button_mail.mail_state == BUTTON_MAIL_PROCESSED){

    			button_mail.mail_state = BUTTON_MAIL_UPDATED;
    			button_mail.button_type = BUTTON_RIGHT;
    			button_mail.button_state = BUTTON_SHORT_PUSHED;

    		}
    	}

    	rot_cnt = 0;


}


//	if (GPIO_Pin == Button_Pin){
//
//		short_clicking = 1;
//
//		HAL_NVIC_DisableIRQ(EXTI4_IRQn);
//
//		HAL_TIM_Base_Start_IT(&htim3);
//		//HAL_NVIC_EnableIRQ(EXTI4_IRQn);
//	}

}


//двигатель
void Relay_Set(uint8_t number, uint8_t flag); //Функция для включения реле, передается номер реле и флаг включения 0-on или 1-off

void Relay_off(); //Отключить реле RL1 и RL2 - функция отключает двигатель
//Функции включения двигателя
void Screw_direct(); //Выставить прямой ход (direct) у двигателя шнека
void Screw_reverse(); //Выставить обратный ход (reverse) у двигателя шнека
void Screw_work(uint8_t direction, uint8_t work_time_sec); //Фукция задающая направление и время работы шнека (секунды 0-180) в этом направлении. Направление (direction) 0 - прямой, 1 - обратный.
//work_time_sec - Время, в течении которого шнек будет включен значения 1-200
//

void Screw_process(uint8_t direction, uint8_t work_time_sec, uint8_t not_work_time_sec); //Функция реализующая алгоритм с задержками. Сначала задержка потом работа.
void Screw_process_repeate(uint8_t direction, uint8_t work_time_sec, uint8_t not_work_time_sec, uint16_t repeate); //тоже самое но с кол-вом повторов repeate


void Relay_Set(uint8_t number, uint8_t flag){

	if(number == 1) HAL_GPIO_WritePin(Relay1_GPIO_Port, Relay1_Pin, flag); //1 - off, 0 - on Реле1 на порту B1
	if(number == 2) HAL_GPIO_WritePin(Relay2_GPIO_Port, Relay2_Pin, flag); //1 - off, 0 - on Реле2 на порту B0

}


void Screw_direct(){

	Relay_Set(2, 1); //Выключаем реле RL2 (обратный ход)

	//HAL_Delay(1000); //Даем реле время на переключение
	if(RELAY_DELAY_ONOFF == 1) osDelay(1000);//Даем реле время на переключение 1 сек

	Relay_Set(1, 0); //Включаем реле RL1 (прямой ход)

}

void Screw_reverse(){

	Relay_Set(1, 1); //Выключаем реле RL1 (прямой ход)

	//HAL_Delay(1000); //Даем реле время на переключение
	if(RELAY_DELAY_ONOFF == 1) osDelay(1000);//Даем реле время на переключение 1 сек

	Relay_Set(2, 0); //Включаем реле RL2 (обратный ход)

}


void Relay_off(){

	Relay_Set(1, 1);
	Relay_Set(2, 1);
	//HAL_Delay(1000); //Даем реле время на переключение
	if(RELAY_DELAY_ONOFF == 1) osDelay(1000);//Даем реле время на переключение 1 сек

}

void Screw_work(uint8_t direction, uint8_t work_time_sec){

	if (direction == 0) Screw_direct(); //прям ход
	if (direction == 1) Screw_reverse(); //обр ход

//	HAL_Delay(work_time_sec*1000); //время которое работает шнек (возможно следует учитывать секунду которая уходит на переключение реле)

	if(1 <= work_time_sec && 200 >= work_time_sec)
		//HAL_Delay(work_time_sec*1000); //время которое работает шнек (возможно следует отнимать секунду которая уходит на переключение реле)
	    osDelay(work_time_sec*1000); //время которое работает шнек (возможно следует отнимать секунду которая уходит на переключение реле)

	Relay_off(); //время work_time_sec достигнуто, значит выключаем все реле

}

void Screw_process(uint8_t direction, uint8_t work_time_sec, uint8_t not_work_time_sec){

	//uint8_t f = 0;
	//возможно следует добавить флаг, чтобы каждый раз не заходить в функции установки входа

	if((1 <= work_time_sec && 200 >= work_time_sec) && (1 <= not_work_time_sec && 200 >= not_work_time_sec)){

	//HAL_Delay(not_work_time_sec*1000); //Задержку реализуем - шнек не работает это время
    osDelay(not_work_time_sec*1000); //Задержку реализуем - шнек не работает это время

	if (direction == 0) Screw_direct(); //прям ход
	if (direction == 1) Screw_reverse();//обр ход

	//HAL_Delay(work_time_sec*1000); //время которое работает шнек (возможно следует отнимать секунду которая уходит на переключение реле)
	osDelay(work_time_sec*1000); //время которое работает шнек

	Relay_off(); //время work_time_sec достигнуто, значит выключаем реле

	}

}


void Screw_process_repeate(uint8_t direction, uint8_t work_time_sec, uint8_t not_work_time_sec, uint16_t repeate){

	//uint32_t T;
	//возможно следует добавить флаг, чтобы каждый раз не заходить в функции установки входа
	for (uint16_t i = 0; i < repeate; i++){

		if((1 <= work_time_sec && 200 >= work_time_sec) && (1 <= not_work_time_sec && 200 >= not_work_time_sec)){

		if (direction == 0) Screw_direct(); //прям ход
		if (direction == 1) Screw_reverse();//обр ход

		osDelay(work_time_sec*1000); //время которое работает шнек

		Relay_off(); //время work_time_sec достигнуто, значит выключаем реле

		osDelay(not_work_time_sec*1000); //Задержку реализуем - шнек не работает это время

		}
	}

}




//Функции вентилятора
void Set_PWM_T3С1(uint16_t value); //Функция настраивает ШИМ, передается значение уровня шим (0-255, где чем выше, тем меньше мощность)
void Set_PWM_ZC_T4C3(uint16_t value); //Функция для установки уровня для вентилятора (0-9000)
void Set_PWM_ZC_T4C3_Percent_Power(uint8_t value_power); //Функция для установки уровня для вентилятора в процентах (10-100), скважность = период/длительность импульса
void Set_PWM_ONOFF(uint8_t flag); //Функция 1включить-0выключить вентилятор
void Set_PWM_ZC_T4C3_Time(uint8_t work_time_sec, uint8_t not_work_time_sec); //Режим продува. Задержка-Работа, настройка времени в секундах
void FINE_TUNING(uint8_t value_power); //Тонкая настройка вентилятора передаем значение в процентах 0-100



void Blowdown(uint8_t work_time_sec, uint8_t not_work_time_sec){


	if((1 <= work_time_sec && 200 >= work_time_sec) && (1 <= not_work_time_sec && 200 >= not_work_time_sec)){


	osDelay(work_time_sec*1000); //время которое работает вентилятор

	flag_pwm_fan = 0;

	osDelay(not_work_time_sec*1000); //Задержку реализуем - вентилятор не работает это время

	flag_pwm_fan = 1;

	}
}






//void Set_PWM_T3С1(uint16_t value){
//
//	TIM3->CCR1 = value; //Записать в регистр таймера 3 канала 1 значения для ШИМ
//
//}


void Set_PWM_ZC_T4C3(uint16_t value){

	__HAL_TIM_SET_COMPARE(&htim4, TIM_CHANNEL_3, value);

}


uint16_t FINE_SET = 0; //точная настройка значение (0-1000), может применять только при 10% мощности т.к. при 10 мощности значение 900 равно и мы можем отнимать до нуля только

void Set_PWM_ZC_T4C3_Percent_Power(uint8_t value_power){

	//uint16_t value =  90 * (100-value_power) - FINE_SET; //90 * (100-value_power) грубая настройка получается, FINE_TUNING точная может применять только при 10% мощности

	if(value_power >= 10 && value_power <= 100 ){

		uint16_t value =  90 * (100-value_power) + FINE_SET; //90 * (100-value_power) грубая настройка получается, FINE_TUNING точная может применять только при 10% мощности

		Set_PWM_ZC_T4C3(value);

	}

}


void Set_PWM_ONOFF(uint8_t flag){

	flag_pwm_fan = flag;

}

//void Set_PWM_ZC_T4C3_Time(uint8_t work_time_sec, uint8_t not_work_time_sec){
//
//	if((1 <= work_time_sec*1000 && 200 >= work_time_sec*1000) && (1 <= not_work_time_sec*1000 && 200 >= not_work_time_sec*1000)){
//
//	Set_PWM_ONOFF(0); //выключить вентилятор
//	HAL_Delay(not_work_time_sec*1000); //подождать время not_work_time_sec
//
//	Set_PWM_ONOFF(1); //включить вентилятор
//	HAL_Delay(work_time_sec*1000); //подождать время work_time_sec
//	Set_PWM_ONOFF(0); //выключить вентилятор
//	}
//}

void FINE_TUNING(uint8_t value_power){

	FINE_SET = value_power*10;

}



//Код для бак полон и пуст:
void Time_Fl(){

	Time_Full = HAL_GetTick();
}

void Time_Emp(){

	Time_Empty = HAL_GetTick();
}

void Time_Fuel_Combustion(){

	Time_Combustion = Time_Full - Time_Empty;
}

uint8_t Percent_Combustion(uint32_t Time_Combustion){

	uint32_t Timer_Percent;
	uint8_t ans;

	Timer_Percent = HAL_GetTick(); //не совсем правда, нужно вычислять сюда именно то время, которое засекается при начале работы котла

	ans = 100 * ((float) (Time_Combustion - Timer_Percent)/Time_Combustion);

	return ans;

}

uint8_t Thermostat_State(){

	uint8_t flag = HAL_GPIO_ReadPin(Thermostat_GPIO_Port, Thermostat_Pin);;

	return flag;
}

float Get_Temp_NTC3435(uint16_t R){ //T(R) = -0.0073751 * R + 91.05

	float Temp;

	//Temp = 110.644633207656 - 0.0188903879012957 * R + 1.06916019165182 *0.000001 * R * R;

	Temp = -31.03*log(R)+310.39;

	return Temp;
}
//void encode_defense_noise(){
//
//	if (ENC_A() == 1)
//	{
//
//	if (count_a < 10){
//		count_a++;}
//
//	else{enc_a = 1;}
//
//	} else{
//
//		if (count_a > 0){
//			count_a--;}
//
//	else {
//		enc_a = 0;}
//	}
//
//
//	//----------------------
//
//
//	if (ENC_B() == 1)
//	{
//
//	if (count_b < 10){
//		count_b++;}
//
//	else {
//		enc_b = 1; }
//	}
//	else
//	{
//
//	if (count_b > 0){
//		count_b--;}
//
//	else {
//		enc_b = 0;}
//	}
//
//}
//
//
//void encode_turn(){
//
//	if (ENC_A() == 1)
//	{
//
//		if (count_a < ENC_DELAY){
//			count_a++;}
//		else
//	 {
//
//		enc_a = 1;
//
//		if (enc_b == 1) {
//			ab = 0;
//		}
//	 }
//	}
//
//	else
//	{
//	if (count_a > 0){
//		count_a--;}
//	else
//	 {
//
//		enc_a = 0;
//
//		if (ab == 0){
//			ab = 1;
//	}
//	else {
//		if(ab == 1) {
//			encoder_state = 1;
//			ab = 2;}
//	    }
//	 }
//	}
//
//	//----------------------
//
//	if (ENC_B() == 1)
//	{
//	if (count_b < ENC_DELAY){
//		count_b++;}
//	else {
//		enc_b = 1;
//
//	if (enc_a == 1) {
//		ab = 0;}}
//	}
//	else
//
//	{
//	if (count_b > 0){
//		count_b--;}
//	else
//	{
//	enc_b = 0;
//
//	if (ab == 0){
//		ab = 1;}
//	else {
//		if(ab == 1) {
//		encoder_state = 2;
//		ab = 2;}}
//	}
//	}
//
//}

//uint16_t Encoder_Value = 0;
//uint8_t NewState, OldState  = 0;
//uint16_t upState, downState;
//void encode(){
////	Encoder_State = 0;
////
//	if(ENC_A() == 1 && ENC_B() == 1){
//		Encoder_State = 3;
//	}
//
//	if(ENC_A() == 1 && ENC_B() == 0){
//		Encoder_State = 2;
//	}
//
//	if(ENC_A() == 0 && ENC_B() == 0){
//		Encoder_State = 0;
//	}
//
//	if(ENC_A() == 0 && ENC_B() == 1){
//		Encoder_State = 1;
//	}
//
////	NewState=ENC_B() & 0b00000011;
////	if(NewState != OldState)
////	{
////	switch(OldState)
////		{
////		case 2:
////			{
////			if(NewState == 3) upState++;
////			if(NewState == 0) downState++;
////			break;
////			}
////
////		case 0:
////			{
////			if(NewState == 2) upState++;
////			if(NewState == 1) downState++;
////			break;
////			}
////		case 1:
////			{
////			if(NewState == 0) upState++;
////			if(NewState == 3) downState++;
////			break;
////			}
////		case 3:
////			{
////			if(NewState == 1) upState++;
////			if(NewState == 2) downState++;
////			break;
////			}
////		}
////	OldState=NewState;
////	}
//
//
////    if (upState >= 4)
////    {
////      Encoder_Value++;
////      upState = 0;
////    }
////    if (downState >= 4)
////    {
////      Encoder_Value--;
////      downState = 0;
////    }
//}

//void encode_switch(){
//
//	switch(Encoder_State)
//		{
//		case 2:
//			{
//			if(NewState == 3) upState++;
//			if(NewState == 0) downState++;
//			break;
//			}
//
//		case 0:
//			{
//			if(NewState == 2) upState++;
//			if(NewState == 1) downState++;
//			break;
//			}
//		case 1:
//			{
//			if(NewState == 0) upState++;
//			if(NewState == 3) downState++;
//			break;
//			}
//		case 3:
//			{
//			if(NewState == 1) upState++;
//			if(NewState == 2) downState++;
//			break;
//			}
//
//}

#endif /* SRC_APP_SENS_AND_ALL_H_ */
