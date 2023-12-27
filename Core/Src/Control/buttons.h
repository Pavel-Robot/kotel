//
// Created by user on 22.08.2022.
//

#ifndef BUTTONS_H
#define BUTTONS_H

#include "buttons_states.h"
//#include "stm32f1xx.h"
//#include "stm32f1xx_ll_gpio.h"

extern void ActionLeft();

extern void ActionCenter();

extern void ActionRight();

void LeftButtonShortPushed() {
    ActionLeft();
}

void LeftButtonLongPushed() {
}

void LeftButtonHandler(uint8_t leftButton) {
    if (leftButton == BUTTON_SHORT_PUSHED) LeftButtonShortPushed();
    if (leftButton == BUTTON_LONG_PUSHED) LeftButtonLongPushed();
    button_mail.mail_state = BUTTON_MAIL_PROCESSED;
}

void CenterButtonShortPushed() {
    ActionCenter();
}

void CenterButtonLongPushed() {
}

void CenterButtonHandler(uint8_t centerButton) {
    if (centerButton == BUTTON_SHORT_PUSHED) CenterButtonShortPushed();
    if (centerButton == BUTTON_LONG_PUSHED) CenterButtonLongPushed();
    button_mail.mail_state = BUTTON_MAIL_PROCESSED;
}

void RightButtonShortPushed() {
    ActionRight();
}

void RightButtonLongPushed() {
}

void RightButtonHandler(uint8_t rightButton) {
    if (rightButton == BUTTON_SHORT_PUSHED) RightButtonShortPushed();
    if (rightButton == BUTTON_LONG_PUSHED) RightButtonLongPushed();
    button_mail.mail_state = BUTTON_MAIL_PROCESSED;
}

void UpdateButtonsStates() {
    if (button_mail.mail_state != BUTTON_MAIL_UPDATED) return;

    switch (button_mail.button_type) {

        case BUTTON_LEFT:
            currentButtons.leftButton = button_mail.button_state;
            break;
        case BUTTON_CENTER:
            currentButtons.centerButton = button_mail.button_state;
            break;
        case BUTTON_RIGHT:
            currentButtons.rightButton = button_mail.button_state;
            break;
        default:
            break;
    }

//    currentButtons.leftButton = (!(LL_GPIO_ReadInputPort(GPIOB) & GPIO_IDR_IDR1));
//    currentButtons.centerButton = (!(LL_GPIO_ReadInputPort(GPIOB) & GPIO_IDR_IDR10));
//    currentButtons.rightButton = (!(LL_GPIO_ReadInputPort(GPIOB) & GPIO_IDR_IDR0));

    if (oldButtonsState.centerButton != currentButtons.centerButton) {
        CenterButtonHandler(currentButtons.centerButton);
        oldButtonsState.centerButton = currentButtons.centerButton;
        return;
    }
    if (oldButtonsState.leftButton != currentButtons.leftButton) {
        LeftButtonHandler(currentButtons.leftButton);
        oldButtonsState.leftButton = currentButtons.leftButton;
        return;
    }
    if (oldButtonsState.rightButton != currentButtons.rightButton) {
        RightButtonHandler(currentButtons.rightButton);
        oldButtonsState.rightButton = currentButtons.rightButton;
        return;
    }
}

#endif //BUTTONS_H
