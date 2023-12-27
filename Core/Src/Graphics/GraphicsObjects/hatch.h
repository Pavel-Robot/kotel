//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_HATCH_H
#define STM32_CONTROLLER_GRAPHICS_HATCH_H

#include "../graphics_models.h"

//Hatch
//top
GraphicPrimitive hatchPoint1 = {POINT, 269, 187};
GraphicPrimitive hatchPoint2 = {LINE, 300, 187};
GraphicPrimitive hatchPoint3 = {DEGREE, 90};
GraphicPrimitive hatchPoint4 = {ARC, 300, 195};
//right
GraphicPrimitive hatchPoint5 = {LINE, 307, 228};
GraphicPrimitive hatchPoint6 = {DEGREE, 90};
GraphicPrimitive hatchPoint7 = {ARC, 300, 228};
//bottom
GraphicPrimitive hatchPoint8 = {LINE, 269, 234};
GraphicPrimitive hatchPoint9 = {DEGREE, 90};
GraphicPrimitive hatchPoint10 = {ARC, 269, 226};
//left
GraphicPrimitive hatchPoint11 = {LINE, 261, 195};
GraphicPrimitive hatchPoint12 = {DEGREE, 90};
GraphicPrimitive hatchPoint13 = {ARC, 269, 195};
//line 1
GraphicPrimitiveSeries hatchLine1 = {13, &hatchPoint1, &hatchPoint2, &hatchPoint3, &hatchPoint4,
                                     &hatchPoint5, &hatchPoint6, &hatchPoint7, &hatchPoint8,
                                     &hatchPoint9, &hatchPoint10, &hatchPoint11, &hatchPoint12, &hatchPoint13};
GraphicObject hatch = {GRAPHICS_PRIMITIVE, 1, &hatchLine1};
//Hatch End

#endif //STM32_CONTROLLER_GRAPHICS_HATCH_H
