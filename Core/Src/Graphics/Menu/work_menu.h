//
// Created by user on 16.09.2022.
//

#ifndef BOILER_GRAPHICS_WORK_MENU_H
#define BOILER_GRAPHICS_WORK_MENU_H

#include "Work/manual_mode_menu.h"

extern void ExitSubmenu();
extern MenuList mainMenuList;

String workMenuElement1Name = {9, "AUTO MODE"};
String workMenuElement2Name = {11, "MANUAL MODE"};
String workMenuElement3Name = {4, "EXIT"};

void ToggleAutoMode() {

}

MenuElement workMenuElement1 = {true, NULL, NULL, ToggleAutoMode, &workMenuElement1Name};
MenuElement workMenuElement2 = {true, &manualModeMenuList, NULL, NULL, &workMenuElement2Name};
MenuElement workMenuElement3 = {true, NULL, NULL, ExitSubmenu, &workMenuElement3Name};

MenuList workMenuList = {&mainMenuList, CLOSE, 0, 3, &workMenuElement1, &workMenuElement2,
                         &workMenuElement3};

#endif //BOILER_GRAPHICS_WORK_MENU_H
