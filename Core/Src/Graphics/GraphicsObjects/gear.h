//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_GEAR_H
#define STM32_CONTROLLER_GRAPHICS_GEAR_H

#include "../graphics_models.h"

//gear start
//gear circle
GraphicPrimitive gearPoint1 = {POINT, 285, 258};
GraphicPrimitive gearPoint2 = {DEGREE, 360};
GraphicPrimitive gearPoint3 = {ARC, 285, 283};
//gear line1
GraphicPrimitiveSeries  gearLine1={3, &gearPoint1, &gearPoint2, &gearPoint3};
//gear pipe
GraphicPrimitive gearPoint4 = {POINT, 309, 275};
GraphicPrimitive gearPoint5 = {LINE, 409, 275};
GraphicPrimitive gearPoint6 = {LINE, 409, 290};
GraphicPrimitive gearPoint7 = {LINE, 309, 290};
//gear line2
GraphicPrimitiveSeries  gearLine2={4, &gearPoint4, &gearPoint5, &gearPoint6, &gearPoint7};
//gear object
GraphicObject gear = {GRAPHICS_PRIMITIVE,2, &gearLine1, &gearLine2};
//gear end

#endif //STM32_CONTROLLER_GRAPHICS_GEAR_H
