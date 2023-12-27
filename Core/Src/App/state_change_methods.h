//
// Created by user on 20.09.2022.
//

#ifndef STATE_CHANGE_METHODS_H
#define STATE_CHANGE_METHODS_H

#include "states.h"

//extern DataContainer manual_fan_power;
void Set_PWM_ZC_T4C3_Percent_Power(uint8_t value_power);
void Pumps_Сentral_Heating(uint8_t flag);
void Pumps_Water_Supply(uint8_t flag);
void Screw_direct();
void Screw_reverse();
void Relay_off();

//FAN

SubjectState GetFanState() {
    return fan_state;
}

void FanStart() {
    if (fan_state!=SUBJECT_ERROR){

        Set_PWM_ZC_T4C3_Percent_Power(manual_fan_power.data);

        fan_state=SUBJECT_RUN;
        flag_pwm_fan = 1;
    }
}

void FanStop() {
    Set_PWM_ZC_T4C3_Percent_Power(0);
    fan_state=SUBJECT_STOP;
    flag_pwm_fan = 0;
}

void FanError() {

}

void ToggleFan() {
    SubjectState temp=GetFanState();
    switch (temp) {
        case SUBJECT_STOP:
            FanStart();
            break;
        case SUBJECT_RUN:
            FanStop();
            break;
        case SUBJECT_ERROR:
        default:
            break;
    }
}

//CENTRAL HEATING PUMP

SubjectState GetPumpCentralHeatingState() {
    return pump_central_heating;
}

void PumpCentralHeatingStart() {
    if (pump_central_heating!=SUBJECT_ERROR){

        //Дополнить логику
        Pumps_Сentral_Heating(0);

        pump_central_heating=SUBJECT_RUN;
    }
}

void PumpCentralHeatingStop() {
    Pumps_Сentral_Heating(1);
    pump_central_heating=SUBJECT_STOP;
}

void PumpCentralHeatingError() {

}

void TogglePumpCentralHeating() {
    SubjectState temp=GetPumpCentralHeatingState();
    switch (temp) {
        case SUBJECT_STOP:
            PumpCentralHeatingStart();
            break;
        case SUBJECT_RUN:
            PumpCentralHeatingStop();
            break;
        case SUBJECT_ERROR:
        default:
            break;
    }
}

//HOT WATER PUMP

SubjectState GetPumpHotWaterState() {
    return pump_hot_water;
}

void PumpHotWaterStart() {
    if (pump_hot_water!=SUBJECT_ERROR){

        //Дополнить логику

        Pumps_Water_Supply(0);

        pump_hot_water=SUBJECT_RUN;
    }
}

void PumpHotWaterStop() {

    Pumps_Water_Supply(1);

    pump_hot_water=SUBJECT_STOP;
}

void PumpHotWaterError() {

}

void TogglePumpHotWater() {
    SubjectState temp=GetPumpHotWaterState();
    switch (temp) {
        case SUBJECT_STOP:
            PumpHotWaterStart();
            break;
        case SUBJECT_RUN:
            PumpHotWaterStop();
            break;
        case SUBJECT_ERROR:
        default:
            break;
    }
}

//SCREW

ScrewState GetScrewState() {
    return screw_state;
}

void ScrewStart() {
    if (screw_state!=SCREW_ERROR){

        //Дополнить логику

        Screw_direct();

        screw_state=SCREW_NORMAL_ROTATE;
    }
}

void ScrewReverseStart() {
    if (screw_state!=SCREW_ERROR){

        //Дополнить логику

        Screw_reverse();

        screw_state=SCREW_REVERSE_ROTATE;
    }
}

void ScrewStop() {

    Relay_off();

    screw_state=SCREW_STOP;
}

void ScrewError() {

}

void ToggleScrew() {
    ScrewState temp=GetScrewState();
    switch (temp) {
        case SCREW_STOP:
            ScrewStart();
            break;
        case SCREW_NORMAL_ROTATE:
        case SCREW_REVERSE_ROTATE:
            ScrewStop();
            break;
        case SCREW_ERROR:
        default:
            break;
    }
}

void ToggleScrewReverse() {
    ScrewState temp=GetScrewState();
    switch (temp) {
        case SCREW_STOP:
            ScrewReverseStart();
            break;
        case SCREW_NORMAL_ROTATE:
        case SCREW_REVERSE_ROTATE:
            ScrewStop();
            break;
        case SCREW_ERROR:
        default:
            break;
    }
}

#endif //STATE_CHANGE_METHODS_H
