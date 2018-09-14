#include "gcn.h"

#define UPDATE_MATH(oldState, newState) oldState << 1 | newState

#define UPDATE_STATE(button)                    \
controller->transitions.button = UPDATE_MATH(   \
    controller->raw.buttons.button,             \
    newState->buttons.button                    \
)

void updateController(Controller* controller, RawState* newState) {
    UPDATE_STATE(A);
    UPDATE_STATE(B);
    UPDATE_STATE(X);
    UPDATE_STATE(Y);

    UPDATE_STATE(L);
    UPDATE_STATE(R);
    UPDATE_STATE(Z);

    UPDATE_STATE(Start);

    UPDATE_STATE(DUp);
    UPDATE_STATE(DRight);
    UPDATE_STATE(DDown);
    UPDATE_STATE(DLeft);
}