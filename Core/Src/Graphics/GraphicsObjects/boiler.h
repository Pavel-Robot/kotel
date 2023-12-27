//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_BOILER_H
#define STM32_CONTROLLER_GRAPHICS_BOILER_H

#include "../graphics_models.h"

#define BoilerStartX    343
#define BoilerStartY    63
#define BoilerWidth     137
#define BoilerHeight    249
#define BoilerAround    20
#define BoilerLineThickness    1

//Boiler
//top
GraphicPrimitive boilerPoint1 = {POINT, BoilerStartX+BoilerAround, BoilerStartY};
GraphicPrimitive boilerPoint2 = {LINE, BoilerStartX+BoilerWidth-BoilerAround, BoilerStartY};
GraphicPrimitive boilerPoint3 = {DEGREE, 90};
GraphicPrimitive boilerPoint4 = {ARC, BoilerStartX+BoilerWidth-BoilerAround, BoilerStartY+BoilerAround};
//right
GraphicPrimitive boilerPoint5 = {LINE, BoilerStartX+BoilerWidth-1, BoilerStartY+BoilerHeight-BoilerAround};
GraphicPrimitive boilerPoint6 = {DEGREE, 90};
GraphicPrimitive boilerPoint7 = {ARC, BoilerStartX+BoilerWidth-BoilerAround, BoilerStartY+BoilerHeight-BoilerAround+2};
//bottom
GraphicPrimitive boilerPoint8 = {LINE, BoilerStartX+BoilerAround, BoilerStartY+BoilerHeight};
GraphicPrimitive boilerPoint9 = {DEGREE, 90};
GraphicPrimitive boilerPoint10 = {ARC, BoilerStartX+BoilerAround, BoilerStartY+BoilerHeight-BoilerAround};
//left
GraphicPrimitive boilerPoint11 = {LINE, BoilerStartX, BoilerStartY+BoilerAround};
GraphicPrimitive boilerPoint12 = {DEGREE, 90};
GraphicPrimitive boilerPoint13 = {ARC, BoilerStartX+BoilerAround, BoilerStartY+BoilerAround};
//line 1
GraphicPrimitiveSeries boilerLine1={13, &boilerPoint1, &boilerPoint2, &boilerPoint3, &boilerPoint4,
                                               &boilerPoint5, &boilerPoint6, &boilerPoint7, &boilerPoint8,
                                               &boilerPoint9, &boilerPoint10, &boilerPoint11, &boilerPoint12, &boilerPoint13};
GraphicObject boiler={GRAPHICS_PRIMITIVE,1,&boilerLine1};
//Boiler End

#endif //STM32_CONTROLLER_GRAPHICS_BOILER_H
