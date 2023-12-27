//
// Created by user on 12.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_TEXTFUNTIONS_H
#define STM32_CONTROLLER_GRAPHICS_TEXTFUNTIONS_H

#include <stddef.h>
#include "stm32_adafruit_lcd.h"
#include "layer_model.h"
#include "colors.h"

typedef struct String_t {
    int countChar;
    char stringData[];
}String;

typedef struct TextObject_t {
    Point shiftXY;
    sFONT *font;
    uint16_t color;
    uint16_t stringsCount;
    String *strings[];
}TextObject;

void DrawText(const char *text, size_t size, uint16_t color, const sFONT *font, uint16_t X, uint16_t Y) {
    BSP_LCD_SetTextColor(color);
    BSP_LCD_SetFont(&Font24);
    uint8_t charWidth = font->Width;
    if (text[size-1]=='\0')--size;
    uint8_t textSize = size / sizeof(char);

    for (int position = 0; position < textSize; ++position) {
        BSP_LCD_DisplayChar(X + charWidth * position, Y, text[position]);
    }
}

void DrawTextObjects(const TextObject *textObject) {
    if (textObject==NULL)return;
    if (textObject->stringsCount < 1)return;
    Point startPoint={GetCurrentLayer()->startPoint.X+textObject->shiftXY.X,
                      GetCurrentLayer()->startPoint.Y+textObject->shiftXY.Y};
    sFONT *font=textObject->font;

    for (int currentLineCount = 0; currentLineCount < textObject->stringsCount; ++currentLineCount) {
        DrawText(textObject->strings[currentLineCount]->stringData,
                 textObject->strings[currentLineCount]->countChar,
                 textObject->color,font,
                 startPoint.X,
                 startPoint.Y+font->Height*currentLineCount);
    }
}

void ClearCharInArea(int x, int y, sFONT *font) {
    uint8_t oldColor=BSP_LCD_GetTextColor();
    BSP_LCD_SetTextColor(colorBlack);
    BSP_LCD_FillRect(x,y,font->Width,font->Height);
    BSP_LCD_SetTextColor(oldColor);
}

uint8_t IntToCharNumber(int number) {
    if (number > 9)return 0;
    return number + '0';
}

#endif //STM32_CONTROLLER_GRAPHICS_TEXTFUNTIONS_H
