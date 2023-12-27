//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_GASPIPE_H
#define STM32_CONTROLLER_GRAPHICS_GASPIPE_H

#include "../graphics_models.h"

#define GasPipeStartX    360
#define GasPipeStartY    5
#define GasPipeWidth     106
#define GasPipeHeight    45
#define GasPipeAround    0
#define GasPipeLineThickness    1

//GasPipe Start
//1
GraphicPrimitive gasPipePoint1 = {POINT, GasPipeStartX, GasPipeStartY};
GraphicPrimitive gasPipePoint2 = {LINE, GasPipeStartX + GasPipeWidth, GasPipeStartY};
GraphicPrimitive gasPipePoint3 = {LINE, GasPipeStartX + GasPipeWidth, GasPipeStartY + GasPipeHeight};
GraphicPrimitive gasPipePoint4 = {LINE, GasPipeStartX, GasPipeStartY + GasPipeHeight};
GraphicPrimitive gasPipePoint5 = {LINE, GasPipeStartX, GasPipeStartY};

GraphicPrimitiveSeries gasPipeLine1 = {5, &gasPipePoint1, &gasPipePoint2, &gasPipePoint3, &gasPipePoint4,
                                           &gasPipePoint5};
//2
GraphicPrimitive gasPipePoint6 = {POINT, GasPipeStartX + GasPipeWidth, GasPipeStartY + 13};
GraphicPrimitive gasPipePoint7 = {LINE, 480, GasPipeStartY + 13};
GraphicPrimitiveSeries gasPipeLine2 = {2, &gasPipePoint6, &gasPipePoint7};
//3
GraphicPrimitive gasPipePoint8 = {POINT, GasPipeStartX + GasPipeWidth, GasPipeStartY + 27};
GraphicPrimitive gasPipePoint9 = {LINE, 480, GasPipeStartY + 27};
GraphicPrimitiveSeries gasPipeLine3 = {2, &gasPipePoint8, &gasPipePoint9};
//4
GraphicPrimitive gasPipePoint10 = {POINT, GasPipeStartX + GasPipeWidth - 45, GasPipeStartY + GasPipeHeight};
GraphicPrimitive gasPipePoint11 = {LINE, GasPipeStartX + GasPipeWidth - 45, GasPipeStartY + GasPipeHeight + 13};
GraphicPrimitiveSeries gasPipeLine4 = {2, &gasPipePoint10, &gasPipePoint11};
//5
GraphicPrimitive gasPipePoint12 = {POINT, GasPipeStartX + GasPipeWidth - 25, GasPipeStartY + GasPipeHeight};
GraphicPrimitive gasPipePoint13 = {LINE, GasPipeStartX + GasPipeWidth - 25, GasPipeStartY + GasPipeHeight + 13};
GraphicPrimitiveSeries gasPipeLine5 = {2, &gasPipePoint12, &gasPipePoint13};
//
GraphicObject gasPipe = {GRAPHICS_PRIMITIVE,5, &gasPipeLine1, &gasPipeLine2, &gasPipeLine3, &gasPipeLine4, &gasPipeLine5};
//GasPipe End

#endif //STM32_CONTROLLER_GRAPHICS_GASPIPE_H
