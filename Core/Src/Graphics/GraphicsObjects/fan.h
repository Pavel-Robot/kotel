//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_FAN_H
#define STM32_CONTROLLER_GRAPHICS_FAN_H

#include "../graphics_models.h"

//Fan Start
//Fan circle
GraphicPrimitive fanPoint1 = {POINT, 235, 258};
GraphicPrimitive fanPoint2 = {DEGREE, 360};
GraphicPrimitive fanPoint3 = {ARC, 235, 283};
//Fan line1
GraphicPrimitiveSeries fanLine1 = {3, &fanPoint1, &fanPoint2, &fanPoint3};
//Fan object
GraphicObject fan = {GRAPHICS_PRIMITIVE, 1, &fanLine1};
//Fan end

#endif //STM32_CONTROLLER_GRAPHICS_FAN_H
