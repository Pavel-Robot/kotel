//
// Created by user on 22.08.2022.
//

#ifndef BUTTONS_STATES_H
#define BUTTONS_STATES_H

#include <stdint.h>

typedef enum ButtonState_t {
    BUTTON_UP = 0,
    BUTTON_SHORT_PUSHED,
    BUTTON_LONG_PUSHED
}ButtonState;

typedef enum ButtonType_t {
    BUTTON_LEFT,
    BUTTON_CENTER,
    BUTTON_RIGHT
} ButtonType;

typedef struct Buttons_t {
    ButtonState leftButton;
    ButtonState centerButton;
    ButtonState rightButton;
} Buttons;

typedef enum ButtonMailState_t {
    BUTTON_MAIL_PROCESSED,
    BUTTON_MAIL_UPDATED
} ButtonMailState;

typedef struct ButtonMail_t {
    ButtonMailState mail_state;
    ButtonType button_type;
    ButtonState button_state;
} ButtonMail;

ButtonMail button_mail;
Buttons oldButtonsState = {BUTTON_UP, BUTTON_UP, BUTTON_UP};
Buttons currentButtons = {BUTTON_UP, BUTTON_UP, BUTTON_UP};

#endif //BUTTONS_STATES_H
