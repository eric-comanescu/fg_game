#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"

class InputManager {
    public:
    enum MotionInputs {
        NONE = 0,

        QCF = 1,
        QCB = 2,
        DP = 3,
        HCF = 4,
    };

    struct Input {
        MotionInputs m_motionInput;
        KeyboardKey m_key;
    };

    Input getInput();
};

#endif
