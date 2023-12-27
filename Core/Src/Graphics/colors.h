//
// Created by user on 22.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_COLORS_H
#define STM32_CONTROLLER_GRAPHICS_COLORS_H

#include "../LCD/stm32_adafruit_lcd.h"

#define color_t uint16_t

const uint16_t colorBlue = LCD_COLOR(20, 100, 246);
const uint16_t colorGreen = LCD_COLOR(36, 224, 36);
const uint16_t colorOrange = LCD_COLOR(255, 102, 36);
const uint16_t colorRed = LCD_COLOR(230, 22, 16);
const uint16_t colorSun = LCD_COLOR(254, 198, 61);
const uint16_t colorBlack = LCD_COLOR(0, 0, 0);
const uint16_t colorWhite = LCD_COLOR(255, 255, 255);
const uint16_t displayColorBackground = colorBlack;

#endif //STM32_CONTROLLER_GRAPHICS_COLORS_H
