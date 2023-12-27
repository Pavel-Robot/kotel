/*
 * Failure.h
 *
 *  Created on: Sep 1, 2022
 *      Author: user
 */

#ifndef SRC_APP_FAILURE_H_
#define SRC_APP_FAILURE_H_

extern uint8_t Encoder_Value;
//extern UART_HandleTypeDef huart3;
//extern osThreadId_t Task_ManageHandle;

void START_WORK_ALL(); // Включаем работу котла:вкл вентилятор, вкл насосы ЦО и ГВС, вкл шнек.
void STOP_WORK_ALL(); //Останавливаем работу котла: выкл вентилятор, выкл насосы ЦО и ГВС, выкл шнек.
void Hand_Fire(); //Режим ручная топка

void START_WORK_ALL_INTEFACES(); //Общая функция с параметрами и выбором режима работы котла, и выбором термостата, выбором типа вентилятора, мощностями

void Temp_Screw(uint8_t temp); //Процедура проверяет температуру на шнеке, если она больше 85, то возникает ошибка "возгорание топлива в трубе шнека" и срабатывает процедура проталкивания до тех пор, пока температура не придет в норму
void Temp_Boiler(uint8_t temp); //Процедура проверяет температуру котла (термик), если больше 90, то выключить вентилятор
void Temp_Gase(uint16_t temp_user, uint16_t temp_now); //Проверка на температуру дымовых газов
void Cover_open(uint8_t state); //Если крышка открыта, то остановить работу котла (учитывается режим work_mode до или после начала работы котла)
void Temp_Сentral_Heating(uint8_t temp); //Если темп ЦО >=40, то выключить насос ЦО - не аварийная ситуация, скорее бытовая
void Current_Screw(float Curr_user, float Curr_now); //Если ток шнека возрос в 2-2.5 раза, то провести процедуру 'реверса-проталкивания'. При этом учитывать попытки, время учета попыток, пороговый ток реверса
void Boiler_Temp_Zero(uint8_t Temp_user, uint8_t Temp_now); //Бойлер погас (котел погас), остановить работу котла. На вход идет температура котла в данный момент и температура установленная пользователем
//void Temp_Street();


void Senn_Connect(uint8_t flag_connect); //Если не подключен хотя бы один датчик, то остановить работу котла



//struct Screw_Settings{ //интересная идея структуры
//
//	uint8_t Power; //Включен ли двигатель 0 - нет, 1 - да
//	uint16_t Current_User; //Пороговый ток реверса от 100 до 5000 мА определенный пользователем
//	uint16_t Current_Screw; //Ток двигателя в данный момент
//	uint8_t Temp_Screw; //Температура шнека в данный момент
//	uint8_t Temp_Screw_User; //Пороговая температура шнека определенная пользователем
//	uint8_t Engine_Vector; //Направление работы двигателя 0 - прям, 1 - обр
//	uint8_t Try; //Кол-во попыток от 2 до 7 определенное пользователем
//	uint32_t Try_Time; //Время учета попыток от 7 до 15 минут
//	uint8_t Flag_error_Curr; //Флаг есть ли сейчас авария с током 0 - нет, 1 - да
//	uint8_t Flag_error_Temp; //Флаг есть ли сейчас авария с температурой 0 - нет, 1 - да
//	//может тут будет еще настройки для разных режимов
//};

uint8_t flag_work = 0; //Запущен ли котел 0 - нет
uint8_t flag_zero_boiler = 0; //флаг, если 0, то не учитывает то, что котел погас
uint8_t flag_mode_support = 0; //флаг, если 0, то пока идет режим нагрева
uint8_t flag_hand_fire = 0; //флаг, если 0, то режим ручная топка выключен
uint8_t flag_thermostat_type = 1; //флаг, типа термостата (0 нормально разомкнутый, 1 нормально замкнутый )
uint8_t flag_Screw_work = 0; //флаг,  если 0, то поток шнека не работает
uint8_t flag_mode_support_onoff = 0; //флаг,  если 0, то режим поддержки не включен
uint8_t flag_error_connect = 0; //флаг, если 0, то ошибки с сенсором нет
uint8_t numer_error_connect = 0; //номер неисправного датчика (0-5 согласно структуре Sens_a)
uint8_t type_error_connect = 0; //тип ошибки 1 - не подключен, 2 - кз 0 - ничего

uint8_t Try_count = 5; // Кол-во попыток реверса, устанавливается пользователем от 2 до 7
uint8_t Fail_current_screw_count = 0; //кол-во аварий шнека подряд
uint8_t Try_Time = 10; // Время учета попыток в минутах (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается (с 7 до 15мин)

//Наметки по состояниям? может пригодится для анализа датчиков и флагов
//typedef struct{
//	//uint8_t flag_work; //Запущен ли котел 0 - нет, 1 - да, (2-остановлен? нужен ли этот параметр)
//	//uint8_t flag_pwm_fan; //Флаг, работает ли вентилятор в данный момент
//
//	uint8_t Temp_Boiler; //Подключен ли температурный датчик 1
//	uint8_t Current_LM321; //Подключен ли температурный датчик 2
//	uint8_t Temp_Screw; //Подключен ли температурный датчик 3
//	uint8_t Temp_Gase; //Подключен ли температурный датчик 4
//	uint8_t Temp_Water; //Подключен ли температурный датчик 5
//	uint8_t Temp_Street; //Подключен ли температурный датчик 6
//
//	uint8_t Hopper_Cover; //Закрыта ли крышка
//
//	uint8_t Thermostat; //Подключен ли термостат
//
////	uint8_t Engine; //Подключен ли двигатель
//
//} State;

//State state;

//typedef struct{
//
//	uint16_t voltage; //напряжение на канале АЦП (милливольты)
//	uint8_t state; //состояние датчика 0 -не подключен (напряжение 3.3в), 1 - подключен (напряжение между 3.3 и 0), 2 - короткое замыкание (напряжение 0)
//
//} Parameters;
//Parameters state_arr[ADC_CHANNELS_NUM];

//typedef struct{
//	//напряжения до подключения с датчиков
//	uint16_t Temp_Boiler_default_voltage; //Температура котла
//	uint16_t Temp_Boiler_d_v_Hysteresis; //Температура котла
//
////	uint16_t Current_LM321_default_voltage; //Ток с LM321
////	uint16_t Current_LM321_d_v_Hysteresis; //Ток с LM321
//
//	uint16_t Temp_Screw_default_voltage; //Температура шнека
//	uint16_t Temp_Screw_d_v_Hysteresis; //Температура шнека
//
//	uint16_t Temp_Gase_default_voltage; //Температура дымовых газов
//	uint16_t Temp_Gase_d_v_Hysteresis; //Температура дымовых газов
//
//	uint16_t Temp_Water_default_voltage; //Температура ГВС
//	uint16_t Temp_Water_d_v_Hysteresis; //Температура ГВС
//
//	uint16_t Temp_Street_default_voltage; //Температура улица
//	uint16_t Temp_Street_d_v_Hysteresise; //Температура улица
//
//} Data_Connect_Sens;
//
//Data_Connect_Sens Sens_voltage = {1000, 100,  1000, 100,  1000, 100,  1000, 100,  1000, 100 };
//uint16_t Sens_voltage_arr[12] = {3300, 100,  3300, 100,  3300, 100,  3300, 100,  3300, 100 };
//uint16_t Sens_voltage_arr2[12] = {1000, 100, 1000, 100,  1000, 100,  1000, 100,  1000, 100,  1000, 100 }; //значения сопротивлений во время работы и их гистерезис

//структура входных данных
typedef struct{

	uint8_t Temp_Boiler_Zero_User; //температура котла при которой котел отключится (будет считаться погасшим)
	uint8_t time_boiler_zero; //время в минутах, которое дается на розжиг котла

	uint16_t Curr_user; //Ток двигателя при зажатой доске, установливается пользователем, диапазон токов 100-5000мА

	uint16_t temp_gase_user; //температура дымовых газов 130-300 (не учитывается первые 15 минут работы котла)


	uint8_t power_fan_rude; //мощность грубая в процентах вентилятора (10-100)
	uint8_t power_fan_perfect; //мощность точная в процентах вентилятора (0-100)
	uint8_t time_fan_work_mode_2; // Время работы вентилятора 0-200 с в режиме поддержки
	uint8_t time_fan_not_work_mode_2; // Время не работы вентилятора 0-200 с в режиме поддержки

	uint8_t time_engine_work_mode_1; // Время работы шнека 0-200 в режиме нагрева
	uint8_t time_engine_not_work_mode_1; //Время не работы шнека 0-200 с в режиме нагрева

	uint8_t time_engine_work_mode_2; // Время работы шнека 0-200 в режиме поддержки
	uint8_t time_engine_not_work_mode_2; //Время не работы шнека 0-200 с в режиме поддержки

	uint8_t Try_count; // Кол-во попыток реверса при аварии шнека, устанавливается пользователем от 2 до 7
	uint8_t Fail_current_screw_count; //кол-во аварий шнека подряд (до Try_count)
	uint8_t Try_Time; // Время учета попыток (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается, диапазон 7-15м

	uint8_t Temp_Central_Heating; //температура ЦО от 45 до 85 - Здесь задаем температуру до которой котел должен греться
	uint8_t Temp_Central_Heating_Hysteresis; //гистерезис ЦО от 1 до 5

	uint8_t Temp_Water; //температура ГВС от 45 до 85 - Здесь задаем температуру до которой ГВС должен греться
	uint8_t Temp_Water_Hysteresis; //гистерезис ГВС от 1 до 5

	uint8_t pump_mode; //Параметр выбора режима по насосам 0-Только насос ЦО 1 - только насос ГВС 2-Насос и ГВС
	uint8_t thermostat_onoff; //Подключен ли термостат 0 - нет, 1 - да
	uint8_t thermostat_type; //Параметр выбора режима по термостату 0-нормально разомкнутый (при нагревании дает 0) 1 - нормально замкнутый (при нагревании дает 1)
	uint8_t fan_mode; //выбор типа вентилятора (у конкурентов только 1 тип)

	//Температурные датчики - подключены 1 или нет 0
	uint8_t state_Boiler;
	uint8_t state_Temp_Screw;
	uint8_t state_Temp_Gase;
	uint8_t state_Temp_Water;
	uint8_t state_Temp_Street;
	uint8_t state_Hopper_Cover;


} INPUT;

//INPUT input = {40, 15, 2000, 300, 80,  5, 5,  10, 60,  10, 2,  0, 10,  1,  60, 1, 3}; //Входные параметры заданные пользователем
INPUT input = {40, 15, 2000, 300, 80, 100,  5, 5,  1, 1,  10, 2,  0, 10,  1,  60, 1, 0, 3, 0}; //Входные параметры заданные пользователем

//Жестко завязанные параметры, как в документации
typedef struct{

	uint8_t temp_sneak_default; // = 85 предельная температура на шнеке temp_sneak >= 85 (если так, то это возгорание шнека)

	uint8_t temp_fan_default; // = 90 предельная температура котла при которой отключается вентилятор

	uint8_t temp_central_heat; // = 40 температура при которой включается насос ЦО

	uint16_t Curr_default;//Ток двигателя при зажатой доске, установлмвается пользователем, диапазон токов 100-5000мА, по умолчанию 1600мА

	uint8_t Try_count_default; // Кол-во попыток реверса при аварии шнека, устанавливается пользователем от 2 до 7, по умолчанию 3
	uint8_t Fail_current_screw_count_default; //кол-во аварий шнека подряд (до Try_count), по умолчанию 0 (всегда ноль)
	uint8_t Try_Time_default; // Время учета попыток (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается, диапазон 7-15м, по умолчанию 10


} INPUT_HARD;

INPUT_HARD input_hard = {85, 90, 40, 1600, 3, 0, 10}; //Входные параметры по умолчанию

////Значения, которые указывают на то, что датчик подключен и работоспособен
//typedef struct{
//
//	uint8_t T1_default_voltage; //температурный датчик 1 - напряжение до подключения
//	uint8_t T2_default_voltage; //температурный датчик 2 - напряжение до подключения
//	uint8_t T3_default_voltage; //температурный датчик 3 - напряжение до подключения
//	uint8_t T4_default_voltage; //температурный датчик 4 - напряжение до подключения
//	uint8_t T5_default_voltage; //температурный датчик 5 - напряжение до подключения
//	uint8_t T6_default_voltage; //температурный датчик 6 - напряжение до подключения
//	uint8_t T7_default_voltage; //температурный датчик 7 - напряжение до подключения
//
//} Data_Connect_Sens;
//
//Data_Connect_Sens Sensor_Connect = {1,1,1,1,1,1,1};

/*
uint8_t ProblemUart[30]; //Массив для UART - отслеживание ошибок
sprintf(str, "1 ADC working!\n ");
HAL_UART_Transmit_IT(&huart3, str, strlen((char *)str));
*/

//для записи ошибок
typedef struct {
	uint8_t Fail_State; //Состояние ошибки 0 - нет, 1 - есть // Для датчиков температуры, тип ошибки: не подключен, кз
	//uint8_t type_error_connect; //Только для датчиков температуры, тип ошибки: не подключен, кз
} FailureCodeTemp;

//Для отслживания ошибко, коррелирует с fail_state_arr
enum Name_Fail {

	//Температура:
	Boiler_overheating, //Перегрев котла - Температура котла превысила 95
	Overheating_screw_pipe, //Перегрев трубы шнека - Температура шнека превысила 85
	Boiler_extinguished, //Котел затух - Температура котла ниже установленного пользователем
	Temperature_smoke_gas_exceeded, //Температура (дымо) газа превышена - 	Температура дымовых газов превысила установлнный порог

	//Прочее (важное тоже):
	Bunker_open, //Бункер открыт - не закрыт топливный бункер
	Hardening_screw //Закливание шнека - Ток потребления электропривода шнека превысил установленное значение.

} name_fail;

FailureCodeTemp fail_state_arr[6];


enum Name_Fail_Sens{

	//Датчики
	Sensor_central_heat_faulty, //Датчик ЦО неисправен - Датчики температуры поврежден, либо отсутствует
	Sensor_water_faulty, //Датчик ГВС неисправен - Датчики температуры поврежден, либо отсутствует
	Sensor_screw_faulty, //Датчик температуры шнека поврежден, либо неисправен
	Sensor_street_faulty, //Авария уличного датчика - датчик уличной температуры вышел из строя или отсутствует
} name_fail_sens;

FailureCodeTemp sens_fail_state_arr[4];




void START_WORK_ALL(){

//	if(flag_work == 0){
//		//Screw_process_repeate(0, 5, 0, 10); // включаем прямой ход (замыкаем цепь прямого хода) - не уверен что так должно быть
//		flag_work = 1; //Указываем, что сейчас система находится во включенном состоянии
//		flag_pwm_fan = 1; //вкл вентилятор
//		Pumps_Сentral_Heating(0); //вкл насос ЦО
//		Pumps_Water_Supply(0); //вкл ГВС
//	}

	if(flag_work == 0){

		flag_work = 1; //Указываем, что сейчас система находится во включенном состоянии
		flag_Screw_work = 1;
		//osThreadSuspend(Task_ManageHandle); //Запускаем поток ответственный за подачу шнека

		//Шнек должен организовывать подачу постепенно из бака
		//Screw_process_repeate(0, 5, 0, 10); // включаем прямой ход (замыкаем цепь прямого хода) - не уверен что так должно быть

		flag_pwm_fan = 1; //вкл вентилятор


		//Включать насос ЦО не требуется т.к. он включится в
		//Pumps_Сentral_Heating(0); //вкл насос ЦО
		//Pumps_Water_Supply(0); //вкл ГВС
	}
}


void STOP_WORK_ALL(){

	if(flag_work == 1){

		flag_work = 0; //Указываем, что сейчас система находится в выключенном состоянии


	//osThreadSuspend(Task_ManageHandle); //Останавливаем поток ответственный за подачу шнека

	Relay_off(); //выкл шнек
	flag_pwm_fan = 0; //выкл вентилятор
	Pumps_Сentral_Heating(1); //выкл насос ЦО
	Pumps_Water_Supply(1); //выкл ГВС
	//нужен флаг, который будет учитывать другие ситуации, чтобы не возникало противоречий, когда все должно быть отключено
	//и когда некоторая ситуация считает (процедура), что раз температура в норме, то продолжаем работать =)

	}
}

void Hand_Fire(){

	//В режиме ручная топка все работает своим ходом, только шнек не работает
	Relay_off(); //выкл шнек
}

void START_WORK_ALL_INTEFACES(){


	//0. Пользователь ввел все параметры в input (А остальные настройки жестко установлены в input_hard)
	//Set_PWM_ZC_T4C3_Percent_Power(input.power_fan_rude); //устанавливаем мощность вентилятора
	//Set_PWM_ZC_T4C3_Percent_Power(rot_cnt); //устанавливаем мощность вентилятора
	Set_PWM_ZC_T4C3_Percent_Power(rot_cnt); //устанавливаем мощность вентилятора
	//Насосы: Блокируем поток, который не нужен т.к. аварии не может произойти без работы данного устройства

//	Set_PWM_ZC_T4C3_Percent_Power(100); //устанавливаем мощность вентилятора
//	osDelay(1000);
//	Set_PWM_ZC_T4C3_Percent_Power(80); //устанавливаем мощность вентилятора
//	osDelay(1000);
//	Set_PWM_ZC_T4C3_Percent_Power(60); //устанавливаем мощность вентилятора
//	osDelay(1000);
//	Set_PWM_ZC_T4C3_Percent_Power(40); //устанавливаем мощность вентилятора
//	osDelay(1000);
//	Set_PWM_ZC_T4C3_Percent_Power(20); //устанавливаем мощность вентилятора
//	osDelay(1000);
//	Set_PWM_ZC_T4C3_Percent_Power(10); //устанавливаем мощность вентилятора
//	osDelay(1000);
//	Set_PWM_ZC_T4C3_Percent_Power(1); //устанавливаем мощность вентилятора
//	osDelay(2000);

	//если подключен темостат, то тоже нужно что-то сделать наверное


	//1. Режим нагрева - вентилятор всегда включен, только определенные настройки шнека
		//1.1 Начало подачи топлива - работает шнек согласно настройкам, НУЖ
		//1.2 Также запускается вентилятор на установленную мощность
		//1.3 Насосы ЦО запускается сам из потока, когда температура больше 40
	START_WORK_ALL();


	//если дошло до определенной температуры котла, то переходим в режим поддержки
	//если дошло до определенной температуры ЦО или ГВС, то находимся в режим поддержки до угасания котла

	//2. Режим поддержки - другие настройки шнека и вентилятора (в режиме продува)

}



void Temp_Screw(uint8_t temp){

	if(temp >= 85){

		//1.Выдать сообщение пользователю "Возгорание в трубе шнека"
		name_fail = Overheating_screw_pipe; //Выбираем номер аварии
		fail_state_arr[name_fail].Fail_State = 1; //Переводим состояние ошибки в активен (1)

		//2.Включить шнек на 2 минуты, сделать паузу в 4 минуты (1 раз это делает)
		Screw_process_repeate(0, 2*60, 4*60, 1);

		//3. Повторить измерение температуры на шнеке
		//если температура равна нормальной T<85 - остановить шнек
		//если не равна, то повторить процедуру еще один раз (повторять до условия <85)

		//+(от себя) возможно записать в журнал, что была такая авария в такое то время
	}

}


void Temp_Boiler(uint8_t temp){

	if(temp >= 90){
		//1. Выключить вентилятор
		flag_pwm_fan = 0;

		//записать ошибку
		name_fail = Boiler_overheating; //Выбираем номер аварии
		fail_state_arr[name_fail].Fail_State = 1; //Переводим состояние ошибки в активен (1)

	}
	//2. Если температура T<90, то вентилятор вновь включается (+от себя - включается только в том случае, если флаг flag_work=1 )
	else{
		if(flag_work == 1) flag_pwm_fan = 1; }

}

void Temp_Gase(uint16_t temp_user, uint16_t temp_now){

	//temp_user = 130-300 градусов

	//Если температура дымовых газов больше, чем установил пользователь
	if(temp_now > temp_user){

		//Сообщить об аварии
		name_fail = Temperature_smoke_gas_exceeded; //Выбираем номер аварии
		fail_state_arr[name_fail].Fail_State = 1; //Переводим состояние ошибки в активен (1)

		//Остановить работу котла
		STOP_WORK_ALL();

	}
}

void Cover_open(uint8_t state){

	//1. Если крышка открыта state = 1 до начала работы котла flag_work = 0
	if(state == 1 && flag_work == 0){



		//2. Не даем запустить котел!
		STOP_WORK_ALL();
	}


	//1. Если крышка открыта state = 1 во время работы котла work_mode = 1
	if(state == 1 && flag_work == 1){

		//2. Остановить работу котла
		STOP_WORK_ALL();


		name_fail = Bunker_open; //Выбираем номер аварии
		fail_state_arr[name_fail].Fail_State = 1; //Переводим состояние ошибки в активен (1)



		//+(от себя) возможно записать в журнал, что была такая авария в такое то время

	}

}


void Temp_Сentral_Heating(uint8_t temp){

//	if(temp >= 40){
//		//1. Включить насос ЦО
//		Pumps_Сentral_Heating(0);
//	}
//	//2. Если температура T<40, то насос должен быть выключен
//	else Pumps_Сentral_Heating(1);

	if(input.pump_mode == 0 || input.pump_mode == 2){
		//возможно такая реализация более сбоеустойчива
		if(temp >= 40){
		//1. Включить насос ЦО
			if(flag_work == 1){
				Pumps_Сentral_Heating(1);
			}
		}
		//2. Если температура T<40, то насос должен быть выключен
		else {
			Pumps_Сentral_Heating(0);
		}
	}


	if(input.pump_mode == 1 || input.pump_mode == 2){
		if(Sens_a.Temp_Water.value >= 40){
		//1. Включить насос ЦО
			if(flag_work == 1){
				Pumps_Water_Supply(1);
			}
		}
		//2. Если температура T<40, то насос должен быть выключен
		else {
			Pumps_Water_Supply(0);
		}

	}



}


void Current_Screw(float Curr_user, float Curr_now){


	//1. Если ток возрос в 2-2.5 раза по сравнению с тем, что определил пользователь (100-5000мА), то
//	if(Curr_now / Curr_user >= 2 && Curr_now / Curr_user <= 2.5){
//
//		Fail_current_screw_count+=1; //Фиксируем, что произошла авария
//
//		if(Fail_current_screw_count < 2){
//
//		//2. Отправляем сообщение пользователю, что заклинило шнек
//
//
//		//3. Останавливаем шнек
//		Relay_off();
//
//		//4. Выполняем процедуру реверса
//		//Сначала в обратную сторону прокрутим шнек 5 секунд
//		Screw_process_repeate(1, 5, 0, 1);
//		//после покрутим вперед шнек на 5 секунд
//		Screw_process_repeate(0, 5, 0, 1);
//
//
//		//5. Проверим ток шнека (+от себя - это будет второе вхождение в функцию)
//		//Если аварии не зафиксировано, то уменьшить попытку на 1 и продолжить работу
//		//Если авария вновь зафиксирована, то проверка попыток, если есть, то отнять попытку и повторить процедуру реверса,
//															  //если нет, то остановить работу котла и записать ошибку в журнал
//
//
//		} else{
//			//Если авария вновь зафиксирована, то проверка попыток, если есть, то отнять попытку и повторить процедуру реверса,
//																		  //если нет, то остановить работу котла и записать ошибку в журнал
//			if(Try_count != 0){
//				Try_count-=1;
//
//				//Процедура реверса
//				//Сначала в обратную сторону прокрутим шнек 5 секунд
//						Screw_process_repeate(1, 5, 0, 1);
//						//после покрутим вперед шнек на 5 секунд
//						Screw_process_repeate(0, 5, 0, 1);
//			} else {
//				STOP_WORK_ALL();
//
//				//Записать ошибку в журнал
//
//			}
//		}
//
//	} else{
//		//Если аварии не зафиксировано, то уменьшить попытку на 1 и продолжить работу
//		if(Fail_current_screw_count == 1) {
//			Try_count-=1;
//		}
//	  }

	//1. Если ток возрос в 2-2.5 раза по сравнению с тем, что определил пользователь (100-5000мА), то
	if(Curr_now / Curr_user >= 2 && Curr_now / Curr_user <= 2.5 && flag_hand_fire == 0){

		Fail_current_screw_count+=1; //Фиксируем, что произошла авария

		if(Fail_current_screw_count < 2){

		//2. Отправляем сообщение пользователю, что заклинило шнек


		//(+от себя) Когда зайдем в функцию и обнаружим аварию, необходимо, чтобы поток остановился StartTask_Manage (во избежание конфликта)
		//osThreadSuspend(Task_ManageHandle); //Останавливаем поток
		flag_work = 0;

		//3. Останавливаем шнек
		Relay_off();

		//4. Выполняем процедуру реверса
		//Сначала в обратную сторону прокрутим шнек 5 секунд
		Screw_process_repeate(1, 5, 0, 1);
		//после покрутим вперед шнек на 5 секунд
		Screw_process_repeate(0, 5, 0, 1);

		//osThreadResume(Task_ManageHandle); //Продолжаем поток
		flag_work = 1;

		//5. Проверим ток шнека (+от себя - это будет второе вхождение в функцию)
		//Если аварии не зафиксировано, то уменьшить попытку на 1 и продолжить работу
		//Если авария вновь зафиксирована, то проверка попыток, если есть, то отнять попытку и повторить процедуру реверса,
															  //если нет, то остановить работу котла и записать ошибку в журнал


		} else{
			//Если авария вновь зафиксирована, то проверка попыток, если есть, то отнять попытку и повторить процедуру реверса,
																		  //если нет, то остановить работу котла и записать ошибку в журнал
			if(Try_count > 0){
				Try_count-=1;

				//Процедура реверса
				//Сначала в обратную сторону прокрутим шнек 5 секунд
						Screw_process_repeate(1, 5, 0, 1);
						//после покрутим вперед шнек на 5 секунд
						Screw_process_repeate(0, 5, 0, 1);
			} else {
				STOP_WORK_ALL();


				//Записать ошибку в журнал
				name_fail = Hardening_screw; //Выбираем номер аварии
				fail_state_arr[name_fail].Fail_State = 1; //Переводим состояние ошибки в активен (1)

			}
		}
	}

//	} else{
//		//Если аварии не зафиксировано, то уменьшить попытку на 1 и продолжить работу
//		if(Fail_current_screw_count == 1) {
//			Try_count-=1;
//		}
//	  }


}


void Boiler_Temp_Zero(uint8_t Temp_user, uint8_t Temp_now){



	//Если температура котла ниже установленной пользователем, то остановить работу котла
	if(Temp_now < Temp_user){

		STOP_WORK_ALL();

		//Записать в журнал
		name_fail = Boiler_extinguished; //Выбираем номер аварии
		fail_state_arr[name_fail].Fail_State = 1; //Переводим состояние ошибки в активен (1)

	}
}


void Senn_Connect(uint8_t flag_connect){

	//смысл в том, что нужно взять диапазон напряжений среди которых датчик будет считаться подключенным
	//if((измеренное на заводе <= Sensor_Connect.T1_default_voltage && Sensor_Connect.T1_default_voltage >= измеренное на заводе+100) || (&& Sensor_Connect.T1_default_voltage => измеренное на заводе))

	//Если не подключены датчики, то отключить котел
	//Когда будет плата, то фактором подключения будет являться напряжение полученное с АЦП



	//if(flag_connect){
	if(flag_error_connect){

		//Если один датчик неисправен, то выдать ошибку c номером датчика

		STOP_WORK_ALL();

		osDelay(5000); //Ждем 5 секунд прежде чем вновь выдать ошибку

	}



	uint16_t v; //буфер напряжения
	for(uint8_t i = 0; i < ADC_CHANNELS_NUM; i++){

		//Если определено пользователем, что датчик подключен
		if(state_arr[i].state == 1){

			//enum Who_I {
			//	Temp_Boiler,
			//	Temp_Screw,
			//	Temp_Gase,
			//	Temp_Water,
			//	Temp_Street,
			//};

			v = state_arr[i].voltage;

			//проверим подключен ли он (если не подключен то напряжение около 3.3в)
			if(3300 - 100 < v && v <= 3300 + 100 ){
				flag_error_connect = 1;

				numer_error_connect = i; //Запоминаем какой датчик был неисправен
				type_error_connect = 1; //Фиксируем, что была ошибка -не подключен датчик

				//name_fail = 100; //Выбираем номер аварии
				//fail_state_arr[name_fail].Fail_State = 1; //Переводим состояние ошибки в активен (1)

				break;
			}
			else{
				flag_error_connect = 0;
			}

			//также проверим на кз
			if( v == 0 ){
				flag_error_connect = 1;

				numer_error_connect = i; //Запоминаем какой датчик был неисправен
				type_error_connect = 2; //Фиксируем, что была ошибка - датчик в кз
				break;
			} else{
				flag_error_connect = 0;
			    }

			//возможно тут будет еще проверка на допустимые значения

		}
	}

	//state_arr[i].state =


	//Сначала проверим на подключен ли датчик в настройках меню
	//for

	//Сначала проверим на КЗ - не равно напряжение нулю ли
	//if(Sens_a.Temp_Boiler.voltage != 0) Sens_a.Temp_Boiler.state = 1; else flag_error_connect = 1;



//	//предельные значения, когда датчик не подключен
//	for(uint8_t i = 0; i < ADC_CHANNELS_NUM; i++){
//
//
//
//
//		//проверка на не равно ли напряжение 0 - это будет кз
//		//if(state_arr[i].voltage > )
//
////		//Sens_voltage_arr[i] - входные данные напряжений с АЦП, которые записываются руками
////		if( adcVoltage[i]/SIZE_AVERAGE - Sens_voltage_arr[2*i+1] <= Sens_voltage_arr[2*i] && Sens_voltage_arr[2*i] <= adcVoltage[2*i]/SIZE_AVERAGE + Sens_voltage_arr[2*i+1] ){
////
////		state_arr[i] = 0; //датчик не подключен
////
////		//STOP_WORK_ALL();
////
////		//(+от себя) по идее номеру датчика соответствует своя ошибка, еще один массив со строками (ошибки типа датчик не подключен)
////		}
////
////
////		//предельные значения, когда датчик подключен
////		//Sens_voltage_arr[i] - входные данные напряжений с АЦП, которые записываются руками
////		if( Get_Resist(adcVoltage[i]/SIZE_AVERAGE - Sens_voltage_arr2[2*i+1]) <= Get_Resist(Sens_voltage_arr2[2*i]) && Get_Resist(Sens_voltage_arr2[2*i]) <= Get_Resist(adcVoltage[2*i]/SIZE_AVERAGE + Sens_voltage_arr2[2*i+1]) ){
////
////		state_arr[i] = 2; //датчик либо неисправен
////
////		//STOP_WORK_ALL();
////
////		//(+от себя) по идее номеру датчика соответствует своя ошибка, еще один массив со строками (ошибки типа датчик неисправен)
////
////		}
//
//	}




//	state.Thermostat = Thermostat_State();
//	state.Hopper_Cover = Hopper_Cover_State();


	//Проверка по напряжению - подключен ли датчик в диапазоне (330 - 100 < IN && IN < 330 + 100)
//	if( adcVoltage[0]/SIZE_AVERAGE - Sens_voltage.Temp_Boiler_d_v_Hysteresis <= Sens_voltage.Temp_Boiler_default_voltage && Sens_voltage.Temp_Boiler_default_voltage <= adcVoltage[0]/SIZE_AVERAGE + Sens_voltage.Temp_Boiler_d_v_Hysteresis )
//	state.Temp_Boiler = 0;
//
//	if( adcVoltage[1]/SIZE_AVERAGE - Sens_voltage.Current_LM321_d_v_Hysteresis <= Sens_voltage.Current_LM321_default_voltage && Sens_voltage.Current_LM321_default_voltage <= adcVoltage[1]/SIZE_AVERAGE + Sens_voltage.Current_LM321_d_v_Hysteresis )
//	state.Current_LM321 = 0;
//
//	if( adcVoltage[2]/SIZE_AVERAGE - Sens_voltage.Temp_Screw_d_v_Hysteresis <= Sens_voltage.Temp_Screw_default_voltage && Sens_voltage.Temp_Screw_default_voltage <= adcVoltage[2]/SIZE_AVERAGE + Sens_voltage.Temp_Screw_d_v_Hysteresis )
//	state.Temp_Screw = 0;
//
//	if( adcVoltage[3]/SIZE_AVERAGE - Sens_voltage.Temp_Gase_d_v_Hysteresis <= Sens_voltage.Temp_Gase_default_voltage && Sens_voltage.Temp_Gase_default_voltage <= adcVoltage[3]/SIZE_AVERAGE + Sens_voltage.Temp_Gase_d_v_Hysteresis )
//	state.Temp_Gase = 0;
//
//	if( adcVoltage[4]/SIZE_AVERAGE - Sens_voltage.Temp_Water_d_v_Hysteresis <= Sens_voltage.Temp_Water_default_voltage && Sens_voltage.Temp_Water_default_voltage <= adcVoltage[4]/SIZE_AVERAGE + Sens_voltage.Temp_Water_d_v_Hysteresis )
//	state.Temp_Water = 0;
//
//	if( adcVoltage[5]/SIZE_AVERAGE - Sens_voltage.Temp_Street_d_v_Hysteresise <= Sens_voltage.Temp_Street_default_voltage && Sens_voltage.Temp_Water_default_voltage <= adcVoltage[5]/SIZE_AVERAGE + Sens_voltage.Temp_Street_d_v_Hysteresise )
//	state.Temp_Street = 0;


}








#endif /* SRC_APP_FAILURE_H_ */
