//
// Created by user on 16.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_MENU_H
#define BOILER_GRAPHICS_SETTINGS_MENU_H

#include "Settings/settings_room_outdoor.h"
#include "Settings/settings_hot_water.h"
#include "Settings/settings_central_heating.h"
#include "Settings/settings_fan.h"
#include "Settings/settings_screw.h"
#include "Settings/settings_schedules.h"
#include "Settings/settings_graph_schedule.h"
#include "Settings/settings_bunker.h"
#include "Settings/settings_accidents.h"
#include "Settings/settings_mobile_app.h"

extern void ExitSubmenu();

extern MenuList mainMenuList;

String settingsMenuElement1Name = {17, "ROOM/OUTDOOR MODE"};
String settingsMenuElement2Name = {18, "SETTINGS HOT WATER"};
String settingsMenuElement3Name = {24, "SETTINGS CENTRAL HEATING"};
String settingsMenuElement4Name = {12, "SETTINGS FAN"};
String settingsMenuElement5Name = {14, "SETTINGS SCREW"};
String settingsMenuElement6Name = {9, "SCHEDULES"};
String settingsMenuElement7Name = {14, "SETTINGS GRAPH"};
String settingsMenuElement8Name = {6, "BUNKER"};
String settingsMenuElement9Name = {9, "ACCIDENTS"};
String settingsMenuElement10Name = {10, "MOBILE APP"};
String settingsMenuElement11Name = {5, "EMPTY"};
String settingsMenuElement12Name = {5, "EMPTY"};
String settingsMenuElement13Name = {4, "EXIT"};

MenuElement settingsMenuElement1 = {true, &roomOutdoorMenuList, NULL, NULL, &settingsMenuElement1Name};
MenuElement settingsMenuElement2 = {true, &settingsHotWaterMenuList, NULL, NULL, &settingsMenuElement2Name};
MenuElement settingsMenuElement3 = {true, &settingsCentralHeatingMenuList, NULL, NULL, &settingsMenuElement3Name};
MenuElement settingsMenuElement4 = {true, &settingsFanMenuList, NULL, NULL, &settingsMenuElement4Name};
MenuElement settingsMenuElement5 = {true, &settingsScrewMenuList, NULL, NULL, &settingsMenuElement5Name};
MenuElement settingsMenuElement6 = {true, &settingsSchedulesMenuList, NULL, NULL, &settingsMenuElement6Name};
MenuElement settingsMenuElement7 = {true, &settingsGraphScheduleMenuList, NULL, NULL, &settingsMenuElement7Name};
MenuElement settingsMenuElement8 = {true, &settingsBunkerMenuList, NULL, NULL, &settingsMenuElement8Name};
MenuElement settingsMenuElement9 = {true, &settingsAccidentsMenuList, NULL, NULL, &settingsMenuElement9Name};
MenuElement settingsMenuElement10 = {true, &settingsMobileAppMenuList, NULL, NULL, &settingsMenuElement10Name};
MenuElement settingsMenuElement11 = {true, NULL, NULL, NULL, &settingsMenuElement11Name};
MenuElement settingsMenuElement12 = {true, NULL, NULL, NULL, &settingsMenuElement12Name};
MenuElement settingsMenuElement13 = {true, NULL, NULL, ExitSubmenu, &settingsMenuElement13Name};

MenuList settingsMenuList = {&mainMenuList, CLOSE, 0, 13,
                             &settingsMenuElement1, &settingsMenuElement2,
                             &settingsMenuElement3, &settingsMenuElement4,
                             &settingsMenuElement5, &settingsMenuElement6,
                             &settingsMenuElement7, &settingsMenuElement8,
                             &settingsMenuElement9, &settingsMenuElement10,
                             &settingsMenuElement11, &settingsMenuElement12,
                             &settingsMenuElement13};

#endif //BOILER_GRAPHICS_SETTINGS_MENU_H
