//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_SCHEDULES_H
#define BOILER_GRAPHICS_SETTINGS_SCHEDULES_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsSchedulesMenuElement1Name = {24, "SCHEDULE CENTRAL HEATING"};
String settingsSchedulesMenuElement2Name = {18, "SCHEDULE HOT WATER"};
String settingsSchedulesMenuElement3Name = {4, "EXIT"};

MenuElement settingsSchedulesMenuElement1 = {true, NULL, NULL, NULL, &settingsSchedulesMenuElement1Name};
MenuElement settingsSchedulesMenuElement2 = {true, NULL, NULL, NULL, &settingsSchedulesMenuElement2Name};
MenuElement settingsSchedulesMenuElement3 = {true, NULL, NULL, ExitSubmenu, &settingsSchedulesMenuElement3Name};

MenuList settingsSchedulesMenuList = {&settingsMenuList, CLOSE, 0, 3,
                                     &settingsSchedulesMenuElement1, &settingsSchedulesMenuElement2,
                                     &settingsSchedulesMenuElement3};

#endif //BOILER_GRAPHICS_SETTINGS_SCHEDULES_H
