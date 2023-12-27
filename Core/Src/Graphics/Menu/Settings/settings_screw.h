//
// Created by user on 19.09.2022.
//

#ifndef BOILER_GRAPHICS_SETTINGS_SCREW_H
#define BOILER_GRAPHICS_SETTINGS_SCREW_H

#include "../../../Settings/settings_user.h"

extern void ExitSubmenu();
extern MenuList settingsMenuList;

String settingsScrewMenuElement1Name = {9, "WORK TIME"};
String settingsScrewMenuElement2Name = {10, "PAUSE TIME"};
String settingsScrewMenuElement3Name = {17, "SUPPORT WORK TIME"};
String settingsScrewMenuElement4Name = {18, "SUPPORT PAUSE TIME"};
String settingsScrewMenuElement5Name = {26, "REVERSE NUMBER OF ATTEMPTS"};
String settingsScrewMenuElement6Name = {14, "REVERSE PERIOD"};
String settingsScrewMenuElement7Name = {17, "CURRENT THRESHOLD"};
String settingsScrewMenuElement8Name = {4, "EXIT"};

MenuElement settingsScrewMenuElement1 = {true, NULL, &mainSettings.screwSettings.heatingUpWorkingTime, NULL, &settingsScrewMenuElement1Name};
MenuElement settingsScrewMenuElement2 = {true, NULL, &mainSettings.screwSettings.heatingUpIdlyTime, NULL, &settingsScrewMenuElement2Name};
MenuElement settingsScrewMenuElement3 = {true, NULL, &mainSettings.screwSettings.supportingWorkingTime, NULL, &settingsScrewMenuElement3Name};
MenuElement settingsScrewMenuElement4 = {true, NULL, &mainSettings.screwSettings.supportingIdlyTime, NULL, &settingsScrewMenuElement4Name};
MenuElement settingsScrewMenuElement5 = {true, NULL, &mainSettings.screwSettings.reverseNumberOfAttempts, NULL, &settingsScrewMenuElement5Name};
MenuElement settingsScrewMenuElement6 = {true, NULL, &mainSettings.screwSettings.reversePeriod, NULL, &settingsScrewMenuElement6Name};
MenuElement settingsScrewMenuElement7 = {true, NULL, &mainSettings.screwSettings.currentThreshold, NULL, &settingsScrewMenuElement7Name};
MenuElement settingsScrewMenuElement8 = {true, NULL, NULL, ExitSubmenu, &settingsScrewMenuElement8Name};

MenuList settingsScrewMenuList = {&settingsMenuList, CLOSE, 0, 8,
                                     &settingsScrewMenuElement1, &settingsScrewMenuElement2,
                                  &settingsScrewMenuElement3, &settingsScrewMenuElement4,
                                  &settingsScrewMenuElement5, &settingsScrewMenuElement6,
                                     &settingsScrewMenuElement7, &settingsScrewMenuElement8};

#endif //BOILER_GRAPHICS_SETTINGS_SCREW_H
