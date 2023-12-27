//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_ACCIDENTS_H
#define BOILER_GRAPHICS_SETTINGS_ACCIDENTS_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsAccidentsMenuElement1Name = {5, "EMPTY"};
String settingsAccidentsMenuElement2Name = {5, "EMPTY"};
String settingsAccidentsMenuElement3Name = {5, "EMPTY"};
String settingsAccidentsMenuElement4Name = {15, "CLEAN ACCIDENTS"};
String settingsAccidentsMenuElement5Name = {4, "EXIT"};

MenuElement settingsAccidentsMenuElement1 = {true, NULL, NULL, NULL, &settingsAccidentsMenuElement1Name};
MenuElement settingsAccidentsMenuElement2 = {true, NULL, NULL, NULL, &settingsAccidentsMenuElement2Name};
MenuElement settingsAccidentsMenuElement3 = {true, NULL, NULL, NULL, &settingsAccidentsMenuElement3Name};
MenuElement settingsAccidentsMenuElement4 = {true, NULL, NULL, NULL, &settingsAccidentsMenuElement4Name};
MenuElement settingsAccidentsMenuElement5 = {true, NULL, NULL, ExitSubmenu, &settingsAccidentsMenuElement5Name};

MenuList settingsAccidentsMenuList = {&settingsMenuList, CLOSE, 0, 5,
                                     &settingsAccidentsMenuElement1, &settingsAccidentsMenuElement2,
                                      &settingsAccidentsMenuElement3, &settingsAccidentsMenuElement4,
                                     &settingsAccidentsMenuElement5};

#endif //BOILER_GRAPHICS_SETTINGS_ACCIDENTS_H
