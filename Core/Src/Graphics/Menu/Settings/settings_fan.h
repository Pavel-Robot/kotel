//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_FAN_H
#define BOILER_GRAPHICS_SETTINGS_FAN_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsFanMenuElement1Name = {9, "FAN SPEED"};
String settingsFanMenuElement2Name = {17, "SUPPORT WORK TIME"};
String settingsFanMenuElement3Name = {18, "SUPPORT PAUSE TIME"};
String settingsFanMenuElement4Name = {4, "EXIT"};

MenuElement settingsFanMenuElement1 = {true, NULL, &mainSettings.fanSettings.heatingUpSpeed, NULL, &settingsFanMenuElement1Name};
MenuElement settingsFanMenuElement2 = {true, NULL, &mainSettings.fanSettings.supportingWorkingTime, NULL, &settingsFanMenuElement2Name};
MenuElement settingsFanMenuElement3 = {true, NULL, &mainSettings.fanSettings.supportingIdlyTime, NULL, &settingsFanMenuElement3Name};
MenuElement settingsFanMenuElement4 = {true, NULL, NULL, ExitSubmenu, &settingsFanMenuElement4Name};

MenuList settingsFanMenuList = {&settingsMenuList, CLOSE, 0, 4,
                                     &settingsFanMenuElement1, &settingsFanMenuElement2,
                                     &settingsFanMenuElement3,&settingsFanMenuElement4};

#endif //BOILER_GRAPHICS_SETTINGS_FAN_H
