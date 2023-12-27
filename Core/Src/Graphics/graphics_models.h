//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_GRAPHICSMODELS_H
#define STM32_CONTROLLER_GRAPHICS_GRAPHICSMODELS_H

#include <stdint.h>
#include "../LCD/stm32_adafruit_lcd.h"

typedef struct Point32_t {
    int X;
    int Y;
} Point32;

typedef enum GraphicColor_t {
    BLACK, WHITE, RED, GREEN, BLUE
} GraphicColor;

uint16_t intColorToUintColor(int16_t color) {
    uint16_t sign = color >> 15;
    uint16_t data = color;
    return (data >> 1) + (sign << 15);
}

int16_t UintColorToIntColor(uint16_t color) {
    uint16_t sign = color >> 15;
    uint16_t data = color;
    return (data >> 1) + (sign << 15);
}

typedef enum GraphicPrimitiveType_t {
    DATA = 0, CIRCLE_CENTER, DEGREE, RADIAN, SIZE, COLOR, POINT, LINE, ARC, RECTANGLE, RECTANGLE_FILLED
} GraphicPrimitiveType;

typedef struct PointFloat_t {
    float X;
    float Y;
} PointFloat, *pPointFloat;

typedef struct GraphicPrimitive_t {
    GraphicPrimitiveType curveType;
    Point point;
} GraphicPrimitive, *pGraphicPrimitive;

typedef struct GraphicPrimitiveSeries_t {
    uint16_t curvePointCount;
    GraphicPrimitive *curvePoints[];
} GraphicPrimitiveSeries, *pGraphicPrimitiveSeries;

typedef enum GraphicObjectType_t {
    GRAPHICS_OBJECT, GRAPHICS_PRIMITIVE, MENU, TEXT, ANIMATION
} GraphicObjectType;

typedef struct GraphicObject_t {
    GraphicObjectType graphicObjectType;
    uint16_t graphicObjectsCount;
    void *subObjects[];
} GraphicObject, *pGraphicObject;

#endif //STM32_CONTROLLER_GRAPHICS_GRAPHICSMODELS_H
