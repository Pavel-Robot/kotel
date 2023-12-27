//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_HOT_WATER_H
#define BOILER_GRAPHICS_SETTINGS_HOT_WATER_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsHotWaterMenuElement1Name = {25, "ONLY CENTRAL HEATING MODE"};
String settingsHotWaterMenuElement2Name = {19, "ONLY HOT WATER MODE"};
String settingsHotWaterMenuElement3Name = {29, "CENTRAL HEATING AND HOT WATER"};
String settingsHotWaterMenuElement4Name = {21, "TEMPERATURE HOT WATER"};
String settingsHotWaterMenuElement5Name = {4, "EXIT"};

void PumpStateToOnlyCH() {
    mainSettings.hotWaterSettings.pumpModeState=PUMP_MODE_CENTRAL_HEATING;
}

void PumpStateToOnlyHW() {
    mainSettings.hotWaterSettings.pumpModeState=PUMP_MODE_HOT_WATER;
}

void PumpStateToBoth() {
    mainSettings.hotWaterSettings.pumpModeState=PUMP_MODE_BOTH;
}

MenuElement settingsHotWaterMenuElement1 = {true, NULL, NULL, PumpStateToOnlyCH, &settingsHotWaterMenuElement1Name};
MenuElement settingsHotWaterMenuElement2 = {true, NULL, NULL, PumpStateToOnlyHW, &settingsHotWaterMenuElement2Name};
MenuElement settingsHotWaterMenuElement3 = {true, NULL, NULL, PumpStateToBoth, &settingsHotWaterMenuElement3Name};
MenuElement settingsHotWaterMenuElement4 = {true, NULL, &mainSettings.hotWaterSettings.targetTemperatureHotWater, NULL, &settingsHotWaterMenuElement4Name};
MenuElement settingsHotWaterMenuElement5 = {true, NULL, NULL, ExitSubmenu, &settingsHotWaterMenuElement5Name};

MenuList settingsHotWaterMenuList = {&settingsMenuList, CLOSE, 0, 5,
                                &settingsHotWaterMenuElement1, &settingsHotWaterMenuElement2,
                                     &settingsHotWaterMenuElement3, &settingsHotWaterMenuElement4,
                                &settingsHotWaterMenuElement5};

#endif //BOILER_GRAPHICS_SETTINGS_HOT_WATER_H
