//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_MOBILE_APP_H
#define BOILER_GRAPHICS_SETTINGS_MOBILE_APP_H

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsMobileAppMenuElement1Name = {9, "CONTROLLER SERIAL NUMBER"};
String settingsMobileAppMenuElement2Name = {11, "CELL SIGNAL STRENGTH"};
String settingsMobileAppMenuElement3Name = {4, "EXIT"};

MenuElement settingsMobileAppMenuElement1 = {true, NULL, NULL, NULL, &settingsMobileAppMenuElement1Name};
MenuElement settingsMobileAppMenuElement2 = {true, NULL, NULL, NULL, &settingsMobileAppMenuElement2Name};
MenuElement settingsMobileAppMenuElement3 = {true, NULL, NULL, ExitSubmenu, &settingsMobileAppMenuElement3Name};

MenuList settingsMobileAppMenuList = {&settingsMenuList, CLOSE, 0, 3,
                                     &settingsMobileAppMenuElement1, &settingsMobileAppMenuElement2,
                                     &settingsMobileAppMenuElement3};

#endif //BOILER_GRAPHICS_SETTINGS_MOBILE_APP_H
