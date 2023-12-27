//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_GRAPH_SCHEDULE_H
#define BOILER_GRAPHICS_SETTINGS_GRAPH_SCHEDULE_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsGraphScheduleMenuElement1Name = {18, "TEMPERATURE AT -10"};
String settingsGraphScheduleMenuElement2Name = {18, "TEMPERATURE AT -25"};
String settingsGraphScheduleMenuElement3Name = {18, "TEMPERATURE AT -40"};
String settingsGraphScheduleMenuElement4Name = {4, "EXIT"};

MenuElement settingsGraphScheduleMenuElement1 = {true, NULL, &mainSettings.graphScheduleSettings.targetTemperatureAt10Negative, NULL, &settingsGraphScheduleMenuElement1Name};
MenuElement settingsGraphScheduleMenuElement2 = {true, NULL, &mainSettings.graphScheduleSettings.targetTemperatureAt25Negative, NULL, &settingsGraphScheduleMenuElement2Name};
MenuElement settingsGraphScheduleMenuElement3 = {true, NULL, &mainSettings.graphScheduleSettings.targetTemperatureAt40Negative, NULL, &settingsGraphScheduleMenuElement3Name};
MenuElement settingsGraphScheduleMenuElement4 = {true, NULL, NULL, ExitSubmenu, &settingsGraphScheduleMenuElement4Name};

MenuList settingsGraphScheduleMenuList = {&settingsMenuList, CLOSE, 0, 4,
                                      &settingsGraphScheduleMenuElement1, &settingsGraphScheduleMenuElement2,
                                      &settingsGraphScheduleMenuElement3, &settingsGraphScheduleMenuElement4};
#endif //BOILER_GRAPHICS_SETTINGS_GRAPH_SCHEDULE_H
