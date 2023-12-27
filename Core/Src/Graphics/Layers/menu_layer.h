//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_MENULAYER_H
#define STM32_CONTROLLER_GRAPHICS_MENULAYER_H

#include <stdlib.h>
#include <string.h>
#include "Menu/main_menu.h"

//Menu layer

GraphicObject currentMenu = {MENU, 1, &mainMenuList};
GraphicLayer menuLayer = {MENU_LAYER_STARTPOINT_X, MENU_LAYER_STARTPOINT_Y, MENU_LAYER_WIDTH, MENU_LAYER_HEIGHT, 2,
                          &mainMenuContour, &currentMenu};

#endif //STM32_CONTROLLER_GRAPHICS_MENULAYER_H
