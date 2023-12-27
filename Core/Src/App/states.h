//
// Created by user on 20.09.2022.
//

#ifndef BOILER_GRAPHICS_STATES_H
#define BOILER_GRAPHICS_STATES_H

#include <stdint.h>
#include "../Settings/settings_model.h"
/*
#define ADC_CHANNELS_NUM 6 //количество каналов для снятия напряжения посредством АЦП
#define REFERENCE_VOLTAGE 3.3 // Опорное напряжение (напряжение питания - можно корректировать)
#define SIZE_AVERAGE 10 //число измерений по которому высчитывается среднее для ацп

#define SENSITY_ACS712 185 //Чувствительность AC712 mV/A
#define SENSITY_UNIT_CURRENT 229 //кол-во единиц измерения АЦП для тока (185*4096/3300) SENSITY_ACS712*4096/REFERENCE_VOLTAGE
#define VALUE_ZERO_ACS_VOLTAGE 1.5 //Значение нуля отсчета тока (значение в вольтах 3.3/2) -Андрей говорит 1.5в, по мое значение 1.15

#define RELAY_DELAY_ONOFF 0 //Если 0, то задержки при переключении реле нет
#define TIME_BUTTON_SHORT 500 //время в мс, короткое нажатие
#define TIME_BUTTON_LONG 1500 //время в мс, длинное нажатие
#define RESIST_DEV 10000 //Значение сопротивления одного резистора в делителе из резисторов (ом)

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

typedef struct {

    uint16_t voltage; //напряжение на канале АЦП (милливольты)
    uint16_t value; //значение параметра для выбранного устройства
    uint8_t state; //состояние датчика 0 -не подключен (напряжение 3.3в), 1 - подключен (напряжение между 3.3 и 0), 2 - короткое замыкание (напряжение 0)

} Parameters;

Parameters state_arr[ADC_CHANNELS_NUM];

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

uint8_t rot_old_state = 0, rot_new_state = 0;
uint8_t rot_cnt = 0;
uint16_t encode_val = 0;

uint8_t NewState = 0, OldState = 0, Vol = 0, upState = 0, downState = 0;
*/

typedef enum AlgorithmMode_t {
    ALGORITHM_AUTO,
    ALGORITHM_MANUAL
} AlgorithmMode;

AlgorithmMode current_algorithm_mode;

typedef enum HeatingState_t {
    HEATING_STOP,
    HEATING_UP,
    HEATING_SUPPORTING,
    HEATING_ERROR
} HeatingState;

HeatingState current_heating_state;

typedef enum ThermostatType_t {
    THERMOSTAT_TYPE_NO = 0,
    THERMOSTAT_TYPE_NC
} ThermostatType;

typedef enum SubjectState_t {
    SUBJECT_STOP,
    SUBJECT_RUN,
    SUBJECT_ERROR
} SubjectState;

typedef enum ScrewState_t {
    SCREW_STOP,
    SCREW_NORMAL_ROTATE,
    SCREW_REVERSE_ROTATE,
    SCREW_ERROR
} ScrewState;

SubjectState fan_state;
DataContainer manual_fan_power= {PERCENTAGE,10,100,50};
SubjectState pump_central_heating;
SubjectState pump_hot_water;

ScrewState screw_state;
/*
uint8_t flag_work = 0; //Запущен ли котел 0 - нет
uint8_t flag_zero_boiler = 0; //флаг, если 0, то не учитывает то, что котел погас
uint8_t flag_mode_support = 0; //флаг, если 0, то пока идет режим нагрева
uint8_t flag_hand_fire = 0; //флаг, если 0, то режим ручная топка выключен
uint8_t flag_thermostat_type = 0; //флаг, типа термостата (0 нормально разомкнутый, 1 нормально замкнутый )
uint8_t flag_Screw_work = 0; //флаг,  если 0, то поток шнека не работает
uint8_t flag_mode_support_onoff = 0; //флаг,  если 0, то режим поддержки не включен
uint8_t flag_error_connect = 0; //флаг, если 0, то ошибки с сенсором нет
uint8_t numer_error_connect = 0; //номер неисправного датчика (0-5 согласно структуре Sens_a)
uint8_t type_error_connect = 0; //тип ошибки 1 - не подключен, 2 - кз 0 - ничего

uint8_t Try_count = 5; // Кол-во попыток реверса, устанавливается пользователем от 2 до 7
uint8_t Fail_current_screw_count = 0; //кол-во аварий шнека подряд
uint8_t Try_Time = 10; // Время учета попыток в минутах (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается (с 7 до 15мин)

//структура входных данных
typedef struct {

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
INPUT input = {40, 15,
               2000, 300, 80,
               100, 5, 5,
               1, 1,
               10, 2,
               0, 10,
               1, 60,
               1, 0,
               3, 0}; //Входные параметры заданные пользователем

//Жестко завязанные параметры, как в документации
typedef struct {

    uint8_t temp_sneak_default; // = 85 предельная температура на шнеке temp_sneak >= 85 (если так, то это возгорание шнека)

    uint8_t temp_fan_default; // = 90 предельная температура котла при которой отключается вентилятор

    uint8_t temp_central_heat; // = 40 температура при которой включается насос ЦО

    uint16_t Curr_default;//Ток двигателя при зажатой доске, установлмвается пользователем, диапазон токов 100-5000мА, по умолчанию 1600мА

    uint8_t Try_count_default; // Кол-во попыток реверса при аварии шнека, устанавливается пользователем от 2 до 7, по умолчанию 3
    uint8_t Fail_current_screw_count_default; //кол-во аварий шнека подряд (до Try_count), по умолчанию 0 (всегда ноль)
    uint8_t Try_Time_default; // Время учета попыток (функция Current_Screw) - Если следующая попытка произошла в течении этого времени, то попытка учитывается, диапазон 7-15м, по умолчанию 10


} INPUT_HARD;

INPUT_HARD input_hard = {85, 90, 40, 1600, 3, 0, 10}; //Входные параметры по умолчанию


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


enum Name_Fail_Sens {

    //Датчики
    Sensor_central_heat_faulty, //Датчик ЦО неисправен - Датчики температуры поврежден, либо отсутствует
    Sensor_water_faulty, //Датчик ГВС неисправен - Датчики температуры поврежден, либо отсутствует
    Sensor_screw_faulty, //Датчик температуры шнека поврежден, либо неисправен
    Sensor_street_faulty, //Авария уличного датчика - датчик уличной температуры вышел из строя или отсутствует
} name_fail_sens;

FailureCodeTemp sens_fail_state_arr[4];


*/
#endif //BOILER_GRAPHICS_STATES_H
