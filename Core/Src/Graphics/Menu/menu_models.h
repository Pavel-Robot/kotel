//
// Created by user on 12.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_MENUMODELS_H
#define STM32_CONTROLLER_GRAPHICS_MENUMODELS_H

#include "../Text/text_funtions.h"
#include "../../Settings/settings_model.h"

typedef enum MenuState_t {
    CLOSE = 0,
    OPEN,
    SUBMENU,
    PARAMETER_DATA
} MenuState;

typedef struct MenuList_t MenuList;

typedef struct MenuElement_t {
    bool active;

    MenuList *submenu;

    DataUnion *data;

    void (*PushAction)();

    String *name;
} MenuElement;

typedef struct MenuList_t {
    struct MenuList_t *parentMenuList;
    MenuState state;
    int selectedElementIndex;
    int elementCount;
    MenuElement *menuElements[];
} MenuList;

#define CarriageCharWidth 17
#define CarriageCharHeight 24
#define CarriageColor colorGreen
String currentMenuCarriage = {2, ">>"};
TextObject currentMenuCarriageTextObject = {0, 0, &Font24, CarriageColor, 1, &currentMenuCarriage};
GraphicPrimitive deleter1MenuCarriageTextObject = {COLOR, colorBlack};
GraphicPrimitive deleter2MenuCarriageTextObject = {DATA, 0, 0};
GraphicPrimitive deleter3MenuCarriageTextObject = {RECTANGLE_FILLED, 0, 0};
GraphicPrimitiveSeries deleterMenuCarriageTextObject = {3, &deleter1MenuCarriageTextObject,
                                                        &deleter2MenuCarriageTextObject,
                                                        &deleter3MenuCarriageTextObject};

#endif //STM32_CONTROLLER_GRAPHICS_MENUMODELS_H
