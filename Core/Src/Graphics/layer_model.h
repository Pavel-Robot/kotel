//
// Created by user on 19.08.2022.
//

#ifndef LAYER_MODEL_H
#define LAYER_MODEL_H

#include <stdint.h>
#include "graphics_models.h"

typedef struct GraphicLayer_t {
    Point startPoint;
    uint16_t width;
    uint16_t height;
    uint16_t graphicsObjectCount;
    GraphicObject *graphicsObject[];
} GraphicLayer, *pGraphicLayer;

GraphicLayer *currentLayer;

GraphicLayer *GetCurrentLayer() {
    return currentLayer;
}

#endif // LAYER_MODEL_H
