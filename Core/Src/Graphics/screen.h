//
// Created by user on 15.09.2022.
//

#ifndef STM32_CONTROLLER_GRAPHICS_SCREEN_H
#define STM32_CONTROLLER_GRAPHICS_SCREEN_H

#include <stdatomic.h>

typedef struct Screen_t {
    atomic_bool needUpdate;
} Screen;

Screen mainScreen;

#endif //STM32_CONTROLLER_GRAPHICS_SCREEN_H
