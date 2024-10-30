#ifndef INPUT_H
#define INPUT_H

#include <cstdint>
#include <queue>
#include <unordered_map>

#include "raylib.h"

class InputManager {
    public:
	enum Direction: uint8_t {
		Up = 0b00001000,
		Down = 0b00000100,
		Left = 0b00000010,
		Right = 0b00000001
	};
	enum AttackType: uint8_t {
		Light = 0b00001000,
		Medium = 0b00000100,
		Heavy = 0b00000010,
		Aerial = 0b00000001
	};

    struct Input {
		uint8_t directionHold;
		uint8_t directionPress;
		uint8_t directionRelease;

		uint8_t attackHold;
		uint8_t attackPress;
		uint8_t attackRelease;
    };

	InputManager();
	~InputManager();

    void buildInputQueue();

	private:
	std::queue<Input> m_inputQueue {};
	std::unordered_map<Direction, KeyboardKey> m_keybinds {
		{ Direction::Up, KEY_W },
		{ Direction::Down, KEY_S },
		{ Direction::Left, KEY_A },
		{ Direction::Right, KEY_D },
	};

	void getHold(Input& input);
	void getPress(Input& input);
	void getRelease(Input& input);

	void sanitizeInputs(Input& input);
	void removeInvalidInputs(Input& input, Direction command1, Direction command2);
};

#endif
