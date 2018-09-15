#include "event.h"

#define HANDLE_TRANSITION(button, fun)                  \
if(controller->transitions.button == RISING) {          \
    fun(device, 1);                                     \
} else if(controller->transitions.button == FALLING) {  \
    fun(device, 0);                                     \
}

#define HANDLE_MOVE(deadzone) {                                     \
    int dx, dy;                                                     \
    dx = dy = 0;                                                    \
    if(controller->raw.mainStick.LR > (128 + deadzone)) dx =  15;   \
    if(controller->raw.mainStick.LR < (128 - deadzone)) dx = -15;   \
    if(controller->raw.mainStick.UD > (128 + deadzone)) dy =  15;   \
    if(controller->raw.mainStick.UD < (128 - deadzone)) dy = -15;   \
    mouseMove(device, dx, dy);                                      \
}

#define HANDLE_SCROLL(deadzone) {                               \
    int dx, dy;                                                 \
    if(controller->raw.cStick.LR > (128 + deadzone)) dx =  2;   \
    if(controller->raw.cStick.LR < (128 - deadzone)) dx = -2;   \
    if(controller->raw.cStick.UD > (128 + deadzone)) dy = -2;   \
    if(controller->raw.cStick.UD < (128 - deadzone)) dy =  2;   \
    mouseScroll(device, dx, dy);                                \
}

void handle_state(Controller* controller, IODevice* device) {
    // A -> leftClick
    HANDLE_TRANSITION(A, leftClick);
    // B -> rightClick
    HANDLE_TRANSITION(B, rightClick);
    // L -> backClick
    HANDLE_TRANSITION(L, backClick);
    // R -> forwardClick
    HANDLE_TRANSITION(R, forwardClick);

    // DUp -> upArrow
    HANDLE_TRANSITION(DUp, upArrow);
    // DRight -> rightArrow
    HANDLE_TRANSITION(DUp, upArrow);
    // DDown -> downArrow
    HANDLE_TRANSITION(DUp, upArrow);
    // DLeft -> leftArrow
    HANDLE_TRANSITION(DUp, upArrow);

    // Start -> Enter
    HANDLE_TRANSITION(Start, enterKey);

    // Y -> Ctrl+Shift+Tab
    HANDLE_TRANSITION(Y, controlKey);
    HANDLE_TRANSITION(Y, shiftKey);
    HANDLE_TRANSITION(Y, tabKey);

    // X -> Ctrl+Tab
    HANDLE_TRANSITION(X, controlKey);
    HANDLE_TRANSITION(X, tabKey);

    // Z -> Alt
    HANDLE_TRANSITION(Z, altKey);

    unsigned char deadzone = 32;
    HANDLE_MOVE(deadzone);
    HANDLE_SCROLL(deadzone);
}