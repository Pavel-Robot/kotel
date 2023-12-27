//
// Created by user on 16.09.2022.
//

#ifndef BOILER_GRAPHICS_MANUAL_MODE_MENU_H
#define BOILER_GRAPHICS_MANUAL_MODE_MENU_H

//#include "Sens_and_all.h"
#include "menu_models.h"
#include "../../../App/state_change_methods.h"

extern void ExitSubmenu();
extern MenuList workMenuList;

String manualModeMenuElement1Name = {9, "Fan Start"};
String manualModeMenuElement2Name = {9, "Fan Speed"};
String manualModeMenuElement3Name = {26, "Pump Central Heating Start"};
String manualModeMenuElement4Name = {20, "Pump Hot Water Start"};
String manualModeMenuElement5Name = {11, "Screw Start"};
String manualModeMenuElement6Name = {19, "Screw Reverse Start"};
String manualModeMenuElement7Name = {4, "EXIT"};

MenuElement manualModeMenuElement1 = {true, NULL, NULL, ToggleFan, &manualModeMenuElement1Name};
MenuElement manualModeMenuElement2 = {true, NULL, NULL, NULL, &manualModeMenuElement2Name};
MenuElement manualModeMenuElement3 = {true, NULL, NULL, TogglePumpCentralHeating, &manualModeMenuElement3Name};
MenuElement manualModeMenuElement4 = {true, NULL, NULL, TogglePumpHotWater, &manualModeMenuElement4Name};
MenuElement manualModeMenuElement5 = {true, NULL, NULL, ToggleScrew, &manualModeMenuElement5Name};
MenuElement manualModeMenuElement6 = {true, NULL, NULL, ToggleScrewReverse, &manualModeMenuElement6Name};
MenuElement manualModeMenuElement7 = {true, NULL, NULL, ExitSubmenu, &manualModeMenuElement7Name};

MenuList manualModeMenuList = {&workMenuList, CLOSE, 0, 7, &manualModeMenuElement1, &manualModeMenuElement2,
                         &manualModeMenuElement3,&manualModeMenuElement4,
                         &manualModeMenuElement5,&manualModeMenuElement6,&manualModeMenuElement7};

#endif //BOILER_GRAPHICS_MANUAL_MODE_MENU_H
