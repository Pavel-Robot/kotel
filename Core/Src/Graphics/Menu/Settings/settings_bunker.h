//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_BUNKER_H
#define BOILER_GRAPHICS_SETTINGS_BUNKER_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsBunkerMenuElement1Name = {11, "BUNKER 100%"};
String settingsBunkerMenuElement2Name = {9, "BUNKER 0%"};
String settingsBunkerMenuElement3Name = {15, "BUNKER DETECTOR"};
String settingsBunkerMenuElement4Name = {4, "EXIT"};

MenuElement settingsBunkerMenuElement1 = {true, NULL, NULL, NULL, &settingsBunkerMenuElement1Name};
MenuElement settingsBunkerMenuElement2 = {true, NULL, NULL, NULL, &settingsBunkerMenuElement2Name};
MenuElement settingsBunkerMenuElement3 = {true, NULL, NULL, NULL, &settingsBunkerMenuElement3Name};
MenuElement settingsBunkerMenuElement4 = {true, NULL, NULL, ExitSubmenu, &settingsBunkerMenuElement4Name};

MenuList settingsBunkerMenuList = {&settingsMenuList, CLOSE, 0, 4,
                                     &settingsBunkerMenuElement1, &settingsBunkerMenuElement2,
                                     &settingsBunkerMenuElement3, &settingsBunkerMenuElement4};

#endif //BOILER_GRAPHICS_SETTINGS_BUNKER_H
