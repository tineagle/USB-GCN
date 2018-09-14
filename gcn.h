#ifndef GCN_H
#define GCN_H

#include <stdint.h>

// [X A B Y L R ZL? ZR] [_ Start _ _ DU DR DD DL]
typedef struct Buttons {
    uint8_t X : 1;
    uint8_t A : 1;
    uint8_t B : 1;
    uint8_t Y : 1;
    uint8_t L : 1;
    uint8_t R : 1;
    uint8_t   : 1;
    uint8_t Z : 1;

    uint8_t       : 1;
    uint8_t Start : 1;
    uint8_t       : 1;
    uint8_t       : 1;
    uint8_t DUp   : 1;
    uint8_t DRight: 1;
    uint8_t DDown : 1;
    uint8_t DLeft : 1;
} Buttons;

// [LR Axis] [UD Axis] - Main Stick
typedef struct MainStick {
    unsigned char LR;
    unsigned char UD;
} MainStick;

// [UD Axis] [LR Axis] - C Stick
typedef struct CStick {
    unsigned char UD;
    unsigned char LR;
} CStick;

// [Left Trigger] [Right Trigger]
typedef struct Triggers {
    unsigned char Left;
    unsigned char Right;
} Triggers;

typedef struct RawState {   // Bytes
    Buttons buttons;        // 2
    MainStick mainStick;    // 2
    CStick cStick;          // 2
    Triggers triggers;      // 2
    char _;                 // 1
} RawState;

typedef enum eButtonTransition {
    LOW     = 0,
    RISING  = 1,
    FALLING = 2,
    HIGH    = 3,
} eButtonTransition;

typedef struct ButtonTransitions {
    eButtonTransition A: 2;
    eButtonTransition B: 2;
    eButtonTransition X: 2;
    eButtonTransition Y: 2;

    eButtonTransition L: 2;
    eButtonTransition R: 2;
    eButtonTransition Z: 2;

    eButtonTransition Start: 2;

    eButtonTransition DUp:      2;
    eButtonTransition DRight:   2;
    eButtonTransition DDown:    2;
    eButtonTransition DLeft:    2;
} ButtonTransitions;

typedef struct Controller {
    RawState raw;
    ButtonTransitions transitions;
} Controller;

void updateController(Controller* controller, RawState* newState);

#endif