//
// Created by user on 22.09.2022.
//

#ifndef MENU_METHODS_H
#define MENU_METHODS_H

#include <stdlib.h>
#include "menu_models.h"
#include "Menu/main_menu.h"
#include "screen.h"
#include "Layers/menu_layer.h"

void NULL_FUNCTION() {};

MenuList *currentMenuList;
MenuElement *currentMenuElement;
Point currentMenuElementXY;

DataUnion *currentData;
color_t menuTextColor;

void UpdateDataOnScreen();

String dataTextString = {1, "0"};
TextObject dataTextObject = {250, (MENU_LAYER_HEIGHT / 2) - 12, &Font24, colorOrange, 1, &dataTextString};

void ClearMenuArea() {
    uint8_t oldColor = BSP_LCD_GetTextColor();
    BSP_LCD_SetTextColor(colorBlack);
    BSP_LCD_FillRect(MENU_LAYER_STARTPOINT_X, MENU_LAYER_STARTPOINT_Y, MENU_LAYER_WIDTH, MENU_LAYER_HEIGHT);
    BSP_LCD_SetTextColor(oldColor);
}

int DisplayInt(uint16_t x, uint16_t y, int number) {
    int remainder = 0;
    int part = 0;
    int chars = 0;
    int absNumber = abs(number);
    uint8_t fontWidth = BSP_LCD_GetFont()->Width;
    if (absNumber < 10) {
        BSP_LCD_DisplayChar(x, y, IntToCharNumber(abs(number)));
        ++chars;
    } else {
        for (int i = 0;; ++i) {
            remainder = absNumber % 10;
            part = absNumber - remainder;
            BSP_LCD_DisplayChar(x - fontWidth * i, y, IntToCharNumber(remainder));
            absNumber /= 10;
            ++chars;
            if (part == 0)break;
        }
    }

    if (number < 0)
        BSP_LCD_DisplayChar(x - fontWidth * chars, y, '-');
    else {
        BSP_LCD_SetTextColor(colorBlack);
        BSP_LCD_DisplayChar(x - fontWidth * chars, y, '-');
    }
    ++chars;
    ClearCharInArea(x - fontWidth * chars, y, BSP_LCD_GetFont());
    return chars;
}

int startMenuDrawIndex=0;

void OpenMenu() {
    currentMenuList->state = OPEN;
    mainMenuList.selectedElementIndex = 0;
    startMenuDrawIndex=0;
    mainScreen.needUpdate = true;
}

void ExitMenu() {
    currentMenuList->state = CLOSE;
    mainMenuList.selectedElementIndex = 0;
    ClearMenuArea();
    mainScreen.needUpdate = true;
}

void UpdateMenuStartIndex();

void ShiftMenuIndexToLeft() {
    if (currentMenuList->selectedElementIndex > 0)--currentMenuList->selectedElementIndex;
    else currentMenuList->selectedElementIndex=currentMenuList->elementCount-1;
    mainScreen.needUpdate = true;
}

void ShiftMenuIndexToRight() {
    if (currentMenuList->selectedElementIndex < currentMenuList->elementCount - 1)
        ++currentMenuList->selectedElementIndex;
    else currentMenuList->selectedElementIndex=0;
    mainScreen.needUpdate = true;
}

void OpenSubmenu() {
    startMenuDrawIndex=0;
    if (currentMenuList->menuElements[currentMenuList->selectedElementIndex]->submenu) {
        currentMenuList->state = SUBMENU;
        MenuList *temp = currentMenuList->menuElements[currentMenuList->selectedElementIndex]->submenu;
        temp->state = OPEN;
        temp->selectedElementIndex = 0;
        currentMenu.subObjects[0]=temp;
        currentMenuList=temp;
        mainScreen.needUpdate = true;
        ClearMenuArea();
    }
    if (currentMenuList->menuElements[currentMenuList->selectedElementIndex]->data) {
        currentMenuList->state = PARAMETER_DATA;
        UpdateDataOnScreen();
    }
    if (currentMenuList->menuElements[currentMenuList->selectedElementIndex]->PushAction) {
        currentMenuList->menuElements[currentMenuList->selectedElementIndex]->PushAction();
    }
}

void ExitSubmenu() {
    currentMenuList->state = CLOSE;
    if (currentMenuList->parentMenuList) {
        currentMenuList = currentMenuList->parentMenuList;
        currentMenu.subObjects[0] = currentMenuList;
        currentMenuList->state = OPEN;
    }
    mainScreen.needUpdate = true;
}

void ExitParameterData() {
    currentMenuList->state = OPEN;
    UpdateDataOnScreen();
}

void CheckCurrentData() {
    if (currentData->dataContainer.data>currentData->dataContainer.max)currentData->dataContainer.data=currentData->dataContainer.max;
    if (currentData->dataContainer.data<currentData->dataContainer.min)currentData->dataContainer.data=currentData->dataContainer.min;
}

void SubtractFromCurrentData() {
    --currentData->dataContainer.data;
    CheckCurrentData();
}

void AddToCurrentData() {
    ++currentData->dataContainer.data;
    CheckCurrentData();
}

void UpdateDataOnScreen() {
    if (currentMenuList->state == PARAMETER_DATA) {
        BSP_LCD_SetTextColor(colorGreen);
        dataTextString.countChar = DisplayInt(MENU_LAYER_STARTPOINT_X + dataTextObject.shiftXY.X,
                                              currentMenuElementXY.Y,
                                              currentData->dataContainer.data);
    }
    if (currentMenuList->state == OPEN) {
        BSP_LCD_SetTextColor(colorOrange);
        for (int i = dataTextString.countChar; i > 0; --i) {
            ClearCharInArea(MENU_LAYER_STARTPOINT_X + dataTextObject.shiftXY.X - (i - 1) * BSP_LCD_GetFont()->Width,
                            currentMenuElementXY.Y, BSP_LCD_GetFont());
        }
    }
}

void DrawCarriage(uint16_t x, uint16_t y, uint16_t color) {
    currentMenuCarriageTextObject.shiftXY.X =
            x - (TEXT_FONT.Width * (currentMenuCarriage.countChar + 1));
    currentMenuCarriageTextObject.shiftXY.Y = y;
    currentMenuCarriageTextObject.color = color;
    DrawTextObjects(&currentMenuCarriageTextObject);
}

void DrawMenuElement(const MenuElement *menuElement, bool selected, int index) {
    if (menuElement == NULL)return;
    color_t tempColorCarriage;
    color_t tempColorMenuElement;
    if (selected == true) {
        tempColorCarriage = CarriageColor;
        tempColorMenuElement = CarriageColor;
    } else {
        tempColorCarriage = colorBlack;
        tempColorMenuElement = menuTextColor;
    }
    Point startPoint = {GetCurrentLayer()->startPoint.X + TEXT_SHIFT_X,
                        GetCurrentLayer()->startPoint.Y + TEXT_SHIFT_Y};
    DrawCarriage(TEXT_SHIFT_X, TEXT_SHIFT_Y + TEXT_FONT.Height * index, tempColorCarriage);
    DrawText(menuElement->name->stringData, menuElement->name->countChar, tempColorMenuElement, &TEXT_FONT,
             startPoint.X, startPoint.Y + TEXT_FONT.Height * index);
}

#define MAX_MENU_ITEMS_DRAW 3

void UpdateMenuStartIndex() {
    if (currentMenuList->selectedElementIndex<startMenuDrawIndex)startMenuDrawIndex=currentMenuList->selectedElementIndex;
    else if(currentMenuList->selectedElementIndex>MAX_MENU_ITEMS_DRAW-1)startMenuDrawIndex=currentMenuList->selectedElementIndex-MAX_MENU_ITEMS_DRAW+1;
    BSP_LCD_SetTextColor(colorOrange);
    DisplayInt(10, 50, startMenuDrawIndex);
    DisplayInt(10, 80, currentMenuList->selectedElementIndex);
}

void DrawMenuList(const MenuList *menuList) {
    if (menuList == NULL)return;
    if (menuList->elementCount < 1)return;

    currentMenuList = menuList;
    menuTextColor = colorOrange;
    bool selectedIndexBool = false;
    uint8_t shiftTextPosition=0;
    UpdateMenuStartIndex();

    for (int8_t currentElementCount = startMenuDrawIndex; currentElementCount < menuList->elementCount; ++currentElementCount) {
        if (startMenuDrawIndex>0){
            BSP_LCD_SetTextColor(colorOrange);
            BSP_LCD_DisplayStringAt(GetCurrentLayer()->startPoint.X + TEXT_SHIFT_X,GetCurrentLayer()->startPoint.Y + TEXT_SHIFT_Y,(uint8_t*)" /\\ ",LEFT_MODE);
            shiftTextPosition=1;
        }
        if(currentElementCount>startMenuDrawIndex+MAX_MENU_ITEMS_DRAW-1){
            break;
        }
        if (currentElementCount == menuList->selectedElementIndex) {
            currentMenuElement = menuList->menuElements[currentElementCount];
            selectedIndexBool = true;
            currentData = currentMenuElement->data;
            //DrawMenuElement(menuList->menuElements[currentElementCount], selectedIndexBool, 0);
        } else selectedIndexBool = false;
        DrawMenuElement(menuList->menuElements[currentElementCount], selectedIndexBool, currentElementCount-startMenuDrawIndex+shiftTextPosition);
        if(menuList->elementCount-MAX_MENU_ITEMS_DRAW-startMenuDrawIndex>0){
            BSP_LCD_SetTextColor(colorOrange);
            BSP_LCD_DisplayStringAt(GetCurrentLayer()->startPoint.X + TEXT_SHIFT_X,GetCurrentLayer()->startPoint.Y + TEXT_SHIFT_Y+ + TEXT_FONT.Height * (MAX_MENU_ITEMS_DRAW+shiftTextPosition),(uint8_t*)" \\/ ",LEFT_MODE);
        }
    }
}

void MenuInit() {
    currentMenuList = &mainMenuList;
}

void ActionLeft() {
    switch (currentMenuList->state) {
        case OPEN:
            ShiftMenuIndexToLeft();
            DrawMenuList(currentMenuList);
            break;
        case PARAMETER_DATA:
            SubtractFromCurrentData();
            UpdateDataOnScreen();
            break;
        case CLOSE:
            break;
    }
}

void ActionCenter() {
    switch (currentMenuList->state) {
        case OPEN:
            OpenSubmenu();
            break;
        case PARAMETER_DATA:
            ExitParameterData();
            break;
        case SUBMENU:
            ExitSubmenu();
            break;
        case CLOSE:
            OpenMenu();
            break;
    }
}

void ActionRight() {
    switch (currentMenuList->state) {
        case OPEN:
            ShiftMenuIndexToRight();
            DrawMenuList(currentMenuList);
            break;
        case PARAMETER_DATA:
            AddToCurrentData();
            UpdateDataOnScreen();
            break;
        case CLOSE:
            break;
    }
}

#endif //MENU_METHODS_H
