//
// Created by user on 11.08.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_BACKGROUNDLAYER_H
#define STM32_CONTROLLER_GRAPHICS_BACKGROUNDLAYER_H

#include "layer_model.h"
#include "../GraphicsObjects/boiler.h"
#include "../GraphicsObjects/fan.h"
#include "../GraphicsObjects/gas_pipe.h"
#include "../GraphicsObjects/gear.h"
#include "../GraphicsObjects/hatch.h"
#include "../GraphicsObjects/water_pipe.h"

//background layer
const GraphicLayer backgroundLayer={0,0,480,320,6, {&boiler,&gear, &fan, &hatch, &gasPipe, &waterPipe}};

#endif //STM32_CONTROLLER_GRAPHICS_BACKGROUNDLAYER_H
