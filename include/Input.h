#ifndef INPUT_H
#define INPUT_H

#include "raylib.h"
#include "StateMachine.h"

class InputManager {
    public:
    enum MotionInputs {
        NONE = 0,

        QCF = 1,
        QCB = 2,
        DP = 3,
        HCF = 4,
    };
	enum Directions {
		DownLeft = 1,
		DownNeutral,
		DownRight,
		NeutralLeft,
		NeutralNeutral,
		NeutralRight,
		UpLeft,
		UpNeutral,
		UpRight
	};

    struct Input {
        MotionInputs motionInput;
        KeyboardKey key;
    };

	InputManager();
	~InputManager();

    Input getInput();

	private:
	StateMachine m_stateMachine;
};

#endif
