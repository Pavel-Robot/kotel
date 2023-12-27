//
// Created by user on 16.09.2022.
//

#ifndef BOILER_GRAPHICS_MAIN_MENU_H
#define BOILER_GRAPHICS_MAIN_MENU_H

#include "work_menu.h"
#include "settings_menu.h"
#include "menu_models.h"

extern void ExitMenu();

#define SCREEN_WIDTH     480
#define SCREEN_HEIGHT     320
#define MENU_LAYER_STARTPOINT_X 50
#define MENU_LAYER_STARTPOINT_Y 50
#define MENU_LAYER_WIDTH (SCREEN_WIDTH-(2*MENU_LAYER_STARTPOINT_X))
#define MENU_LAYER_HEIGHT (100+CarriageCharWidth+15)
//#define MENU_LAYER_HEIGHT (SCREEN_HEIGHT-(2*MENU_LAYER_STARTPOINT_Y))
#define MENU_CONTURE_X 0
#define MENU_CONTURE_Y 0
#define MENU_CONTURE_WIDTH MENU_LAYER_WIDTH
#define MENU_CONTURE_HEIGHT MENU_LAYER_HEIGHT
#define MENU_CONTURE_COLOR colorBlue
#define MENU_BACKGROUND_COLOR colorBlack
#define TEXT_SHIFT_X    (CarriageCharWidth*4+5)
#define TEXT_SHIFT_Y    10
#define TEXT_LINE_HEIGHT    30
#define TEXT_LINE_SHIFT
#define TEXT_FONT Font24

GraphicPrimitive menuStartColor1 = {COLOR, MENU_CONTURE_COLOR};
GraphicPrimitive menuStartPoint1 = {DATA, MENU_CONTURE_X, MENU_CONTURE_Y};
GraphicPrimitive menuRectConf1 = {RECTANGLE, MENU_CONTURE_WIDTH, MENU_CONTURE_HEIGHT};

GraphicPrimitive menuStartColor2 = {COLOR, MENU_CONTURE_COLOR};
GraphicPrimitive menuStartPoint2 = {DATA, MENU_CONTURE_X + 1, MENU_CONTURE_Y + 1};
GraphicPrimitive menuRectConf2 = {RECTANGLE, MENU_CONTURE_WIDTH - 2, MENU_CONTURE_HEIGHT - 2};

GraphicPrimitive menuStartColor3 = {COLOR, MENU_CONTURE_COLOR};
GraphicPrimitive menuStartPoint3 = {DATA, MENU_CONTURE_X + 2, MENU_CONTURE_Y + 2};
GraphicPrimitive menuRectConf3 = {RECTANGLE, MENU_CONTURE_WIDTH - 4, MENU_CONTURE_HEIGHT - 4};

GraphicPrimitive menuStartColor4 = {COLOR, MENU_BACKGROUND_COLOR};
GraphicPrimitive menuStartPoint4 = {DATA, MENU_CONTURE_X + 3, MENU_CONTURE_Y + 3};
GraphicPrimitive menuRectConf4 = {RECTANGLE_FILLED, MENU_CONTURE_WIDTH - 6, MENU_CONTURE_HEIGHT - 6};

GraphicPrimitiveSeries menuRect1 = {3, &menuStartColor1, &menuStartPoint1, &menuRectConf1};
GraphicPrimitiveSeries menuRect2 = {3, &menuStartColor2, &menuStartPoint2, &menuRectConf2};
GraphicPrimitiveSeries menuRect3 = {3, &menuStartColor3, &menuStartPoint3, &menuRectConf3};
GraphicPrimitiveSeries menuRect4 = {3, &menuStartColor4, &menuStartPoint4, &menuRectConf4};

GraphicObject menuContour = {GRAPHICS_PRIMITIVE, 4, &menuRect1, &menuRect2, &menuRect3, &menuRect4};

String mainMenuElement1Name = {4, "WORK"};
String mainMenuElement2Name = {5, "SETUP"};
String mainMenuElement3Name = {4, "EXIT"};

MenuElement mainMenuElement1 = {true, &workMenuList, NULL, NULL, &mainMenuElement1Name};
MenuElement mainMenuElement2 = {true, &settingsMenuList, NULL, NULL, &mainMenuElement2Name};
MenuElement mainMenuElement3 = {true, NULL, NULL, ExitMenu, &mainMenuElement3Name};

MenuList mainMenuList = {NULL, CLOSE, 0, 3, &mainMenuElement1, &mainMenuElement2,
                         &mainMenuElement3};
GraphicObject mainMenu = {MENU, 1, &mainMenuList};
GraphicObject mainMenuContour = {GRAPHICS_OBJECT, 1, &menuContour};

#endif //BOILER_GRAPHICS_MAIN_MENU_H
