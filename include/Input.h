#ifndef INPUT_H
#define INPUT_H

#include <unordered_map>

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
		Directions direction;
    };

	InputManager();
	~InputManager();

    Input getInput();

	private:
	StateMachine m_stateMachine;
	// std::unordered_map<KeyboardKey, Directions> m_player1Keybinds {
	// 	{ KEY_W, Directions::UpNeutral },
	// 	{ KEY_A, Directions::NeutralLeft },
	// 	{ KEY_S, Directions::DownNeutral },
	// 	{ KEY_D, Directions::NeutralRight },
	// };
	// Above line violate multiple initialization rule oops
	// Maybe doesn't violate ODR and mingw32-make is broken?
	std::unordered_map<KeyboardKey, Directions> m_player1Keybinds;
};

#endif
