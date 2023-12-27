//
// Created by user on 20.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_MODEL_H
#define BOILER_GRAPHICS_SETTINGS_MODEL_H

#include <stdint.h>

typedef enum DataType_t {
    CELSIUS,
    AMPERE,
    SECONDS,
    MINUTES,
    ATTEMPTS,
    PERCENTAGE,
    BOOL
} DataType;

typedef struct DataContainer_t {
    DataType dataType;
    const uint8_t min;
    const uint8_t max;
    uint8_t data;
} DataContainer;

typedef union DataUnion_t {
    DataContainer dataContainer;
    uint32_t dataRaw;
} DataUnion;

typedef struct ScrewSettings_t {
    DataUnion heatingUpWorkingTime;
    DataUnion heatingUpIdlyTime;
    DataUnion supportingWorkingTime;
    DataUnion supportingIdlyTime;
    DataUnion reverseNumberOfAttempts;
    DataUnion reversePeriod;
    DataUnion currentThreshold;
} ScrewSettings;

typedef struct FanSettings_t {
    DataUnion heatingUpSpeed;
    DataUnion supportingWorkingTime;
    DataUnion supportingIdlyTime;
} FanSettings;

typedef struct CentralHeatingSettings_t {
    DataUnion targetTemperatureCentralHeating;
    DataUnion hysteresisTemperatureCentralHeating;
    DataUnion smokeDetector;
    DataUnion smokeDetectorTemperature;
    DataUnion decayTemperature;
    DataUnion decayTime;
} CentralHeatingSettings;

typedef enum PumpMode_t {
    PUMP_MODE_CENTRAL_HEATING,
    PUMP_MODE_HOT_WATER,
    PUMP_MODE_BOTH
} PumpMode;

typedef struct HotWaterSettings_t {
    PumpMode pumpModeState;
    DataUnion targetTemperatureHotWater;
} HotWaterSettings;

typedef struct GraphScheduleSettings_t {
    DataUnion targetTemperatureAt10Negative;
    DataUnion targetTemperatureAt25Negative;
    DataUnion targetTemperatureAt40Negative;
} GraphScheduleSettings;

typedef enum GSMStates_t {
    GSM_OFF,
    GSM_ON
} GSMState;

typedef struct GSMSettings_t {
    GSMState enabled;
} GSMSettings;

typedef struct Settings_t {
    ScrewSettings screwSettings;
    FanSettings fanSettings;
    CentralHeatingSettings centralHeatingSettings;
    HotWaterSettings hotWaterSettings;
    GraphScheduleSettings graphScheduleSettings;
} Settings;

#endif //BOILER_GRAPHICS_SETTINGS_MODEL_H
