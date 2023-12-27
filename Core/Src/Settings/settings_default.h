//
// Created by user on 20.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_DEFAULT_H
#define BOILER_GRAPHICS_SETTINGS_DEFAULT_H

#include "settings_model.h"

#define screwHeatingUpWorkingTimeDataType       SECONDS
#define screwHeatingUpWorkingTimeMinLimit       1
#define screwHeatingUpWorkingTimeMaxLimit       180
#define screwHeatingUpWorkingTimeDefault        180
#define screwHeatingUpIdlyTimeDataType          SECONDS
#define screwHeatingUpIdlyTimeMinLimit          1
#define screwHeatingUpIdlyTimeMaxLimit          180
#define screwHeatingUpIdlyTimeDefault           180
#define screwSupportingWorkingTimeDataType      SECONDS
#define screwSupportingWorkingTimeMinLimit      1
#define screwSupportingWorkingTimeMaxLimit      180
#define screwSupportingWorkingTimeDefault       180
#define screwSupportingIdlyTimeDataType         SECONDS
#define screwSupportingIdlyTimeMinLimit         1
#define screwSupportingIdlyTimeMaxLimit         180
#define screwSupportingIdlyTimeDefault          180
#define screwReverseNumberOfAttemptsDataType    ATTEMPTS
#define screwReverseNumberOfAttemptsMinLimit    0
#define screwReverseNumberOfAttemptsMaxLimit    7
#define screwReverseNumberOfAttemptsDefault     5
#define screwReversePeriodDataType              MINUTES
#define screwReversePeriodMinLimit              7
#define screwReversePeriodMaxLimit              15
#define screwReversePeriodDefault               15
#define screwCurrentThresholdDataType           AMPERE
#define screwCurrentThresholdMinLimit           1
#define screwCurrentThresholdMaxLimit           50
#define screwCurrentThresholdDefault            50

#define defaultScrewSettings {\
        screwHeatingUpWorkingTimeDataType,  screwHeatingUpWorkingTimeMinLimit,  screwHeatingUpWorkingTimeMaxLimit,  screwHeatingUpWorkingTimeDefault,\
        screwHeatingUpIdlyTimeDataType,     screwHeatingUpIdlyTimeMinLimit,     screwHeatingUpIdlyTimeMaxLimit,     screwHeatingUpIdlyTimeDefault,\
        screwSupportingWorkingTimeDataType, screwSupportingWorkingTimeMinLimit, screwSupportingWorkingTimeMaxLimit, screwSupportingWorkingTimeDefault,\
        screwSupportingIdlyTimeDataType,    screwSupportingIdlyTimeMinLimit,    screwSupportingIdlyTimeMaxLimit,    screwSupportingIdlyTimeDefault,\
        screwReverseNumberOfAttemptsDataType,screwReverseNumberOfAttemptsMinLimit,screwReverseNumberOfAttemptsMaxLimit,screwReverseNumberOfAttemptsDefault,\
        screwReversePeriodDataType,         screwReversePeriodMinLimit,         screwReversePeriodMaxLimit,         screwReversePeriodDefault,\
        screwCurrentThresholdDataType,      screwCurrentThresholdMinLimit,      screwCurrentThresholdMaxLimit,      screwCurrentThresholdDefault}

#define fanHeatingUpSpeedDataType           PERCENTAGE
#define fanHeatingUpSpeedMinLimit           10
#define fanHeatingUpSpeedMaxLimit           100
#define fanHeatingUpSpeedDefault            100
#define fanSupportingWorkingTimeDataType    SECONDS
#define fanSupportingWorkingTimeMinLimit    1
#define fanSupportingWorkingTimeMaxLimit    180
#define fanSupportingWorkingTimeDefault     180
#define fanSupportingIdlyTimeDataType       SECONDS
#define fanSupportingIdlyTimeMinLimit       1
#define fanSupportingIdlyTimeMaxLimit       180
#define fanSupportingIdlyTimeDefault        180

#define defaultFanSettings {\
        fanHeatingUpSpeedDataType,      fanHeatingUpSpeedMinLimit,      fanHeatingUpSpeedMaxLimit,      fanHeatingUpSpeedDefault,\
        fanSupportingWorkingTimeDataType,fanSupportingWorkingTimeMinLimit,fanSupportingWorkingTimeMaxLimit,fanSupportingWorkingTimeDefault,\
        fanSupportingIdlyTimeDataType,  fanSupportingIdlyTimeMinLimit,  fanSupportingIdlyTimeMaxLimit,  fanSupportingIdlyTimeDefault}

#define centralHeatingTargetTemperatureDataType         CELSIUS
#define centralHeatingTargetTemperatureMinLimit         40
#define centralHeatingTargetTemperatureMaxLimit         85
#define centralHeatingTargetTemperatureDefault          85
#define centralHeatingHysteresisTemperatureDataType     CELSIUS
#define centralHeatingHysteresisTemperatureMinLimit     40
#define centralHeatingHysteresisTemperatureMaxLimit     85
#define centralHeatingHysteresisTemperatureDefault      85
#define centralHeatingSmokeDetectorDataType             BOOL
#define centralHeatingSmokeDetectorMinLimit             0
#define centralHeatingSmokeDetectorMaxLimit             1
#define centralHeatingSmokeDetectorDefault              1
#define centralHeatingSmokeDetectorTemperatureDataType  CELSIUS
#define centralHeatingSmokeDetectorTemperatureMinLimit  12
#define centralHeatingSmokeDetectorTemperatureMaxLimit  30
#define centralHeatingSmokeDetectorTemperatureDefault   30
#define centralHeatingDecayTemperatureDataType          CELSIUS
#define centralHeatingDecayTemperatureMinLimit          20
#define centralHeatingDecayTemperatureMaxLimit          40
#define centralHeatingDecayTemperatureDefault           40
#define centralHeatingDecayTimeDataType                 MINUTES
#define centralHeatingDecayTimeMinLimit                 1
#define centralHeatingDecayTimeMaxLimit                 20
#define centralHeatingDecayTimeDefault                  20

#define defaultCentralHeatingSettings {\
        centralHeatingTargetTemperatureDataType,    centralHeatingTargetTemperatureMinLimit,        centralHeatingTargetTemperatureMaxLimit,        centralHeatingTargetTemperatureDefault,\
        centralHeatingHysteresisTemperatureDataType,centralHeatingHysteresisTemperatureMinLimit,    centralHeatingHysteresisTemperatureMaxLimit,    centralHeatingHysteresisTemperatureDefault,\
        centralHeatingSmokeDetectorDataType,        centralHeatingSmokeDetectorMinLimit,            centralHeatingSmokeDetectorMaxLimit,            centralHeatingSmokeDetectorDefault,\
        centralHeatingSmokeDetectorTemperatureDataType,centralHeatingSmokeDetectorTemperatureMinLimit,centralHeatingSmokeDetectorTemperatureMaxLimit,centralHeatingSmokeDetectorTemperatureDefault,\
        centralHeatingDecayTemperatureDataType,     centralHeatingDecayTemperatureMinLimit,         centralHeatingDecayTemperatureMaxLimit,         centralHeatingDecayTemperatureDefault,\
        centralHeatingDecayTimeDataType,            centralHeatingDecayTimeMinLimit,                centralHeatingDecayTimeMaxLimit,                centralHeatingDecayTimeDefault}

#define targetTemperatureHotWaterDataType   CELSIUS
#define targetTemperatureHotWaterMinLimit   40
#define targetTemperatureHotWaterMaxLimit   85
#define targetTemperatureHotWaterDefault    85

#define defaultHotWaterSettings {\
        PUMP_MODE_BOTH,\
        targetTemperatureHotWaterDataType,  targetTemperatureHotWaterMinLimit,  targetTemperatureHotWaterMaxLimit,  targetTemperatureHotWaterDefault}

#define graphScheduleTargetTemperatureAt10NegativeDataType  CELSIUS
#define graphScheduleTargetTemperatureAt10NegativeMinLimit  40
#define graphScheduleTargetTemperatureAt10NegativeMaxLimit  85
#define graphScheduleTargetTemperatureAt10NegativeDefault   85
#define graphScheduleTargetTemperatureAt25NegativeDataType  CELSIUS
#define graphScheduleTargetTemperatureAt25NegativeMinLimit  40
#define graphScheduleTargetTemperatureAt25NegativeMaxLimit  85
#define graphScheduleTargetTemperatureAt25NegativeDefault   85
#define graphScheduleTargetTemperatureAt40NegativeDataType  CELSIUS
#define graphScheduleTargetTemperatureAt40NegativeMinLimit  40
#define graphScheduleTargetTemperatureAt40NegativeMaxLimit  85
#define graphScheduleTargetTemperatureAt40NegativeDefault   85

#define defaultGraphScheduleSettings {\
        graphScheduleTargetTemperatureAt10NegativeDataType, graphScheduleTargetTemperatureAt10NegativeMinLimit, graphScheduleTargetTemperatureAt10NegativeMaxLimit, graphScheduleTargetTemperatureAt10NegativeDefault,\
        graphScheduleTargetTemperatureAt25NegativeDataType, graphScheduleTargetTemperatureAt25NegativeMinLimit, graphScheduleTargetTemperatureAt25NegativeMaxLimit, graphScheduleTargetTemperatureAt25NegativeDefault,\
        graphScheduleTargetTemperatureAt40NegativeDataType, graphScheduleTargetTemperatureAt40NegativeMinLimit, graphScheduleTargetTemperatureAt40NegativeMaxLimit, graphScheduleTargetTemperatureAt40NegativeDefault}

Settings defaultSettings = {defaultScrewSettings, defaultFanSettings,
                            defaultCentralHeatingSettings, defaultHotWaterSettings,
                            defaultGraphScheduleSettings};

#endif //BOILER_GRAPHICS_SETTINGS_DEFAULT_H
