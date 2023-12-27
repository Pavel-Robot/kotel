//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_WATERPIPE_H
#define STM32_CONTROLLER_GRAPHICS_WATERPIPE_H

#include "../graphics_models.h"

//WaterPipe Start
//1
GraphicPrimitive waterPipePoint1 = {POINT, 180, 5};
GraphicPrimitive waterPipePoint2 = {LINE, 270, 5};
GraphicPrimitive waterPipePoint3 = {LINE, 270, 50};
GraphicPrimitive waterPipePoint4 = {LINE, 180, 50};
GraphicPrimitive waterPipePoint5 = {LINE, 180, 5};
GraphicPrimitiveSeries waterPipeLine1 = {5, &waterPipePoint1, &waterPipePoint2, &waterPipePoint3, &waterPipePoint4,
                                         &waterPipePoint5};
//2
GraphicPrimitive waterPipePoint6 = {POINT, 270, 18};
GraphicPrimitive waterPipePoint7 = {LINE, 280, 18};
GraphicPrimitive waterPipePoint8 = {DEGREE, 90};
GraphicPrimitive waterPipePoint9 = {ARC, 280, 33};
GraphicPrimitive waterPipePoint10 = {LINE, 294, 70};
GraphicPrimitive waterPipePoint11 = {DEGREE, -90};
GraphicPrimitive waterPipePoint12 = {ARC, 300, 70};
GraphicPrimitive waterPipePoint13 = {LINE, 343, 75};
GraphicPrimitiveSeries waterLine2 = {8, &waterPipePoint6, &waterPipePoint7, &waterPipePoint8,
                                     &waterPipePoint9, &waterPipePoint10, &waterPipePoint11,
                                     &waterPipePoint12, &waterPipePoint13,};
//3
GraphicPrimitive waterPipePoint14 = {POINT, 270, 31};
GraphicPrimitive waterPipePoint15 = {LINE, 279, 31};
GraphicPrimitive waterPipePoint16 = {DEGREE, 90};
GraphicPrimitive waterPipePoint17 = {ARC, 279, 36};
GraphicPrimitive waterPipePoint18 = {LINE, 283, 77};
GraphicPrimitive waterPipePoint19 = {DEGREE, -90};
GraphicPrimitive waterPipePoint20 = {ARC, 294, 77};
GraphicPrimitive waterPipePoint21 = {LINE, 343, 87};
GraphicPrimitiveSeries waterLine3 = {8, &waterPipePoint14, &waterPipePoint15, &waterPipePoint16,
                                     &waterPipePoint17, &waterPipePoint18, &waterPipePoint19,
                                     &waterPipePoint20, &waterPipePoint21,};

GraphicObject waterPipe = {GRAPHICS_PRIMITIVE, 3, &waterPipeLine1, &waterLine2, &waterLine3};
//WaterPipe End

#endif //STM32_CONTROLLER_GRAPHICS_WATERPIPE_H
