//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_DRAWFUNCTIONS_H
#define STM32_CONTROLLER_GRAPHICS_DRAWFUNCTIONS_H

#include <math.h>
#include "stm32_adafruit_lcd.h"
#include "layer_model.h"
#include "menu_models.h"
#include "screen.h"
#include "menu_methods.h"
#include "layers.h"

void DrawArc1(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, int16_t degree) {
    int32_t D;       /* Decision Variable */
    uint32_t CurX;   /* Current X Value */
    uint32_t CurY;   /* Current Y Value */

    uint16_t color = BSP_LCD_GetTextColor();       /* Decision Variable */

    D = 3 - (Radius << 1);
    CurX = 0;
    CurY = Radius;

    while ((CurX <= CurY) && degree) {
        degree--;

        BSP_LCD_DrawPixel((Xpos + CurX), (Ypos - CurY), color);
        BSP_LCD_DrawPixel((Xpos - CurX), (Ypos - CurY), color);
        BSP_LCD_DrawPixel((Xpos + CurY), (Ypos - CurX), color);
        BSP_LCD_DrawPixel((Xpos - CurY), (Ypos - CurX), color);
        BSP_LCD_DrawPixel((Xpos + CurX), (Ypos + CurY), color);
        BSP_LCD_DrawPixel((Xpos - CurX), (Ypos + CurY), color);
        BSP_LCD_DrawPixel((Xpos + CurY), (Ypos + CurX), color);
        BSP_LCD_DrawPixel((Xpos - CurY), (Ypos + CurX), color);

        if (D < 0) {
            D += (CurX << 2) + 6;
        } else {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }
}

void DrawArc2(uint16_t Xpos, uint16_t Ypos, uint16_t Radius, int16_t degree) {
    int32_t D;       /* Decision Variable */
    uint32_t CurX;   /* Current X Value */
    uint32_t CurY;   /* Current Y Value */

    int16_t color = BSP_LCD_GetTextColor();       /* Decision Variable */

    D = 3 - (Radius << 1);
    CurX = 0;
    CurY = Radius;
    const uint8_t degree_8 = degree >> 3;

    while ((CurX <= CurY)) {
        //degree--;
        //degree*=2;

        //1
        //if(degree<degree_8) goto end;

        BSP_LCD_DrawPixel((Xpos + CurX + cos(degree)), (Ypos - CurY + sin(degree)), LCD_COLOR(255, 0, 0));


//        //2
//        if(degree<degree_8*2) goto end;
//        BSP_LCD_DrawPixel((Xpos - CurX), (Ypos - CurY), LCD_COLOR(0, 255, 0));
//        //7
//        if(degree<degree_8*3) goto end;
//        BSP_LCD_DrawPixel((Xpos + CurY), (Ypos + CurX), LCD_COLOR(0, 255, 255));
//        //5
//        if(degree<degree_8*4) goto end;
//        BSP_LCD_DrawPixel((Xpos + CurX), (Ypos + CurY), LCD_COLOR(255, 0, 255));
//        //6
//        if(degree<degree_8*5) goto end;
//        BSP_LCD_DrawPixel((Xpos - CurX), (Ypos + CurY), LCD_COLOR(255, 255, 0));
//        //8
//        if(degree<degree_8*6) goto end;
//        BSP_LCD_DrawPixel((Xpos - CurY), (Ypos + CurX), LCD_COLOR(100, 100, 100));
//        //4
//        if(degree<degree_8*7) goto end;
//        BSP_LCD_DrawPixel((Xpos - CurY), (Ypos - CurX), LCD_COLOR(255, 255, 255));
//        //3
//        if(degree<degree_8*8) goto end;
//        BSP_LCD_DrawPixel((Xpos + CurY), (Ypos - CurX), LCD_COLOR(0, 0, 255));

        end:

        if (D < 0) {
            D += (CurX << 2) + 6;
        } else {
            D += ((CurX - CurY) << 2) + 10;
            CurY--;
        }
        CurX++;
    }
}

Point DrawArc(const Point start, const Point circleCenter,const float degree) {
    if (degree==0)return start;
    const float radian = degree * (float) 0.01745329251;
    const int X = (start.X - circleCenter.X);
    const int Y = (start.Y - circleCenter.Y);
    const float radius = sqrtf(X * X + Y * Y);
    const float radianOfStartPoint = -atan2f(X, Y) + M_PI_2;
    const float radianStep = 1 / radius;
    uint16_t color = BSP_LCD_GetTextColor();

    float outputPointX;
    float outputPointY;
    Point point;

    if (radian > 0)
        for (float currentRadian = 0; currentRadian < radian; currentRadian += radianStep) {
            outputPointX = cosf(currentRadian + radianOfStartPoint) * radius + circleCenter.X;
            outputPointY = sinf(currentRadian + radianOfStartPoint) * radius + circleCenter.Y;
            if (outputPointX >= 0 && outputPointY >= 0)
                BSP_LCD_DrawPixel(outputPointX, outputPointY, color);
        }
    else
        for (float currentRadian = 0; currentRadian > radian; currentRadian -= radianStep) {
            outputPointX = cosf(currentRadian + radianOfStartPoint) * radius + circleCenter.X;
            outputPointY = sinf(currentRadian + radianOfStartPoint) * radius + circleCenter.Y;
            if (outputPointX >= 0 && outputPointY >= 0)
                BSP_LCD_DrawPixel(outputPointX, outputPointY, color);
        }
    point.X = outputPointX;
    point.Y = outputPointY;
    return point;
}

Point Rotate(Point point, Point centerPoint, const float radius, const float degree) {

    const double radian = degree * 0.01745329251;
    const double radianOfStartPoint = -atan2(point.X - centerPoint.X, point.Y - centerPoint.Y) + M_PI_2;

    const Point outPoint = {
            cosf(radian + radianOfStartPoint) * radius + centerPoint.X,
            sinf(radian + radianOfStartPoint) * radius + centerPoint.Y};

    return outPoint;
}

void RotateOld(Point points[], size_t size, const float radian) {
    float dln = sqrtf(powf((points[0].X - points[1].X), 2) + powf((points[0].Y - points[1].Y), 2));
    const int16_t radius = (int16_t) (0.57735026918962576450914878050196 * dln);
    const int16_t x0 = (points[0].X + points[1].X + points[2].X) / 3;
    const int16_t y0 = (points[0].Y + points[1].Y + points[2].Y) / 3;
    const Point point0 = {x0, y0};
    int16_t i_x;
    int16_t i_y;

    for (int i = 0; i < size; ++i) {
        i_x = points[i].X - point0.X;
        i_y = points[i].Y - point0.Y;
        points[i].X = i_x * cosf(radian) - i_y * sinf(radian) + point0.X;
        points[i].Y = i_x * sinf(radian) + i_y * cosf(radian) + point0.Y;
    }
}

void DrawArcOld(const Point start, const Point circleCenter, const float degree) {
    float radian = degree * 0.01745329251;
    const uint16_t X = start.X - circleCenter.X;
    const uint16_t Y = start.Y - circleCenter.Y;
    const float radius = sqrtf(X * X + Y * Y);
    const float degree2 = atan2f(X, Y);
    float acc = 1 / radius;

    if (radian > 0)
        for (float x = 0; x < fabs(radian); x += acc) {
            uint16_t xx = (int16_t) (cosf(x + degree2) * radius) + circleCenter.X;
            uint16_t yy = (int16_t) (sinf(x + degree2) * radius) + circleCenter.Y;
            if (xx && yy)
                BSP_LCD_DrawPixel(xx, yy, LCD_COLOR(255, 255, 255));
        }
    else
        for (float x = 0; x > radian; x -= acc) {
            uint16_t xx = (uint16_t) (cosf(x + degree2) * radius) + circleCenter.X;
            uint16_t yy = (uint16_t) (sinf(x + degree2) * radius) + circleCenter.Y;
            if (xx && yy)
                BSP_LCD_DrawPixel(xx, yy, LCD_COLOR(255, 255, 255));
        }
}

float Distance(const Point *pointFirst, const Point *pointSecond) {
    const int32_t distanceX = (pointFirst->X - pointSecond->X);
    const int32_t distanceY = (pointFirst->Y - pointSecond->Y);
    const float distance = sqrtf(distanceX * distanceX + distanceY * distanceY);
    return distance;
}

Point CenterOfPoints(Point points[], size_t size) {
    uint16_t X = 0, Y = 0;
    for (int i = 0; i < size; ++i) {
        X += points[i].X;
        Y += points[i].Y;
    }
    const Point centerPoint = {X / 3,
                               Y / 3};
    return centerPoint;
}

void DrawGraphicPrimitive(const GraphicPrimitiveSeries *curveLine) {
    if (curveLine == NULL || currentLayer == NULL)return;
    uint16_t pointsCount = curveLine->curvePointCount;
    if (pointsCount < 1)return;

    const Point startPoint = currentLayer->startPoint;
    Point prevPoint;
    Point currentPoint;
    Point data;
    uint16_t size;
    Point circleCenterPoint;
    float degree;
    float radian;
    uint16_t color;

    for (uint16_t currentPointCount = 0; currentPointCount < pointsCount; ++currentPointCount) {
        const GraphicPrimitive curvePoint = *curveLine->curvePoints[currentPointCount];
        switch (curvePoint.curveType) {
            case POINT:
                BSP_LCD_DrawPixel(curvePoint.point.X + startPoint.X, curvePoint.point.Y + startPoint.Y, color);
                prevPoint.X = curvePoint.point.X + startPoint.X;
                prevPoint.Y = curvePoint.point.Y + startPoint.Y;
                break;
            case CIRCLE_CENTER:
                break;
            case DEGREE:
                degree = curvePoint.point.X;
                break;
            case RADIAN:
                radian = *(float *) curvePoint.point.X;
                break;
            case ARC:
                circleCenterPoint.X = curvePoint.point.X + startPoint.X;
                circleCenterPoint.Y = curvePoint.point.Y + startPoint.Y;
                prevPoint = DrawArc(prevPoint, circleCenterPoint, degree);
                break;
            case RECTANGLE:
                BSP_LCD_DrawRect(data.X + currentLayer->startPoint.X, data.Y + currentLayer->startPoint.Y,
                                 curvePoint.point.X, curvePoint.point.Y);
                prevPoint.X = (data.X + curvePoint.point.X + startPoint.X);
                prevPoint.Y = (data.Y + curvePoint.point.Y + startPoint.Y);
                break;
            case RECTANGLE_FILLED:
                BSP_LCD_FillRect(data.X + currentLayer->startPoint.X, data.Y + currentLayer->startPoint.Y,
                                 curvePoint.point.X, curvePoint.point.Y);
                prevPoint.X = (data.X + curvePoint.point.X + startPoint.X);
                prevPoint.Y = (data.Y + curvePoint.point.Y + startPoint.Y);
                break;
            case DATA:
                data = curvePoint.point;
                break;
            case SIZE:
                size = curvePoint.point.X;
                break;
            case COLOR:
                BSP_LCD_SetTextColor(curvePoint.point.X);
                color = curvePoint.point.X;
                break;
            case LINE:
                currentPoint.X = curvePoint.point.X + startPoint.X;
                currentPoint.Y = curvePoint.point.Y + startPoint.Y;
                BSP_LCD_DrawLine(prevPoint.X, prevPoint.Y,
                                 currentPoint.X, currentPoint.Y);
                prevPoint = currentPoint;
                break;
        }
    }
}

extern void DrawMenuList(const MenuList *menuList);

void DrawGraphicsObject(const GraphicObject *graphicObject) {
    if (graphicObject == NULL)return;
    if (graphicObject->graphicObjectsCount < 1)return;

    void (*JumpFunction)();

    switch (graphicObject->graphicObjectType) {

        case GRAPHICS_OBJECT:
            JumpFunction = &DrawGraphicsObject;
            break;
        case GRAPHICS_PRIMITIVE:
            JumpFunction = &DrawGraphicPrimitive;
            break;
        case MENU:
            JumpFunction = &DrawMenuList;
            break;
        case TEXT:
            JumpFunction = &DrawTextObjects;
            break;
        case ANIMATION:
            break;
    }

    for (int currentGraphicObjectCount = 0;
         currentGraphicObjectCount < graphicObject->graphicObjectsCount; ++currentGraphicObjectCount) {
        JumpFunction(graphicObject->subObjects[currentGraphicObjectCount]);
    }
}

void DrawGraphicsLayer(const GraphicLayer *graphicLayer) {
    if (graphicLayer->graphicsObjectCount < 0)return;

    currentLayer = graphicLayer;

    for (int currentLineCount = 0; currentLineCount < graphicLayer->graphicsObjectCount; ++currentLineCount) {
        DrawGraphicsObject(graphicLayer->graphicsObject[currentLineCount]);
    }
}

void UpdateScreen() {
    if (mainScreen.needUpdate==true) {
        if (currentMenuList->state == CLOSE) {
            BSP_LCD_SetTextColor(colorBlue);
            DrawGraphicsLayer(&backgroundLayer);
            DrawGraphicsLayer(&textLayer);
        }
        if (currentMenuList->state >= OPEN) {
            DrawGraphicsLayer(&menuLayer);
        }

        mainScreen.needUpdate=false;
    }
}

void UpdateLayers();

GraphicPrimitive gearPointAnimated1 = {CIRCLE_CENTER, 285, 283};
GraphicPrimitive gearPointAnimated2 = {POINT, 285, 265};

#endif //STM32_CONTROLLER_GRAPHICS_DRAWFUNCTIONS_H
