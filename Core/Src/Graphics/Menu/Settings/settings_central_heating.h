//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_CENTRAL_HEATING_H
#define BOILER_GRAPHICS_SETTINGS_CENTRAL_HEATING_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();

extern MenuList settingsMenuList;



String settingsCentralHeatingMenuElement1Name = {27, "TEMPERATURE CENTRAL HEATING"};
String settingsCentralHeatingMenuElement2Name = {10, "HYSTERESIS"};
String settingsCentralHeatingMenuElement3Name = {21, "SMOKE DETECTOR OFF/ON"};
String settingsCentralHeatingMenuElement4Name = {26, "TEMPERATURE SMOKE DETECTOR"};
String settingsCentralHeatingMenuElement5Name = {17, "DECAY TEMPERATURE"};
String settingsCentralHeatingMenuElement6Name = {10, "DECAY TIME"};
String settingsCentralHeatingMenuElement7Name = {4, "EXIT"};

MenuElement settingsCentralHeatingMenuElement1 = {true, NULL, &mainSettings.centralHeatingSettings.targetTemperatureCentralHeating, NULL, &settingsCentralHeatingMenuElement1Name};
MenuElement settingsCentralHeatingMenuElement2 = {true, NULL, &mainSettings.centralHeatingSettings.hysteresisTemperatureCentralHeating, NULL, &settingsCentralHeatingMenuElement2Name};
MenuElement settingsCentralHeatingMenuElement3 = {true, NULL, &mainSettings.centralHeatingSettings.smokeDetector, NULL, &settingsCentralHeatingMenuElement3Name};
MenuElement settingsCentralHeatingMenuElement4 = {true, NULL, &mainSettings.centralHeatingSettings.smokeDetectorTemperature, NULL, &settingsCentralHeatingMenuElement4Name};
MenuElement settingsCentralHeatingMenuElement5 = {true, NULL, &mainSettings.centralHeatingSettings.decayTemperature, NULL, &settingsCentralHeatingMenuElement5Name};
MenuElement settingsCentralHeatingMenuElement6 = {true, NULL, &mainSettings.centralHeatingSettings.decayTime, NULL, &settingsCentralHeatingMenuElement6Name};
MenuElement settingsCentralHeatingMenuElement7 = {true, NULL, NULL, ExitSubmenu,
                                                  &settingsCentralHeatingMenuElement7Name};

MenuList settingsCentralHeatingMenuList = {&settingsMenuList, CLOSE, 0, 7,
                                           &settingsCentralHeatingMenuElement1, &settingsCentralHeatingMenuElement2,
                                           &settingsCentralHeatingMenuElement3, &settingsCentralHeatingMenuElement4,
                                           &settingsCentralHeatingMenuElement5, &settingsCentralHeatingMenuElement6,
                                           &settingsCentralHeatingMenuElement7};

#endif //BOILER_GRAPHICS_SETTINGS_CENTRAL_HEATING_H
