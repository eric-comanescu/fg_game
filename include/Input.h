#ifndef INPUT_H
#define INPUT_H

#include <cstdint>
#include <queue>
#include <unordered_map>

#include "raylib.h"

class InputManager {
    public:
	enum Movement {
		Up = 0b1000,
		Down = 0b0100,
		Left = 0b0010,
		Right = 0b0001
	};
	enum AttackType {
		Light = 0b1000,
		Medium = 0b0100,
		Heavy = 0b0010,
		Aerial = 0b0001
	};

    struct Input {
		uint8_t movementHold;
		uint8_t movementPress;
		uint8_t movementRelease;

		uint8_t attackHold;
		uint8_t attackPress;
		uint8_t attackRelease;
    };

	InputManager();
	~InputManager();

    void updateInput();

	private:
	std::queue<Input> m_inputQueue {};
	std::unordered_map<Movement, KeyboardKey> m_keybinds {
		{ Movement::Up, KEY_W },
		{ Movement::Down, KEY_S },
		{ Movement::Left, KEY_A },
		{ Movement::Right, KEY_D },
	};
};

#endif
