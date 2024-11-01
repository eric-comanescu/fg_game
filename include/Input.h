#ifndef INPUT_H
#define INPUT_H

#include <cstdint>
#include <list>
#include <unordered_map>

#include "raylib.h"

class InputManager {
public:
	enum Action {
		Up_Input,
		Down_Input,
		Left_Input,
		Right_Input,
		Light_Input,
		Medium_Input,
		Heavy_Input
	};
    enum DirectionMask: uint8_t {
        Up = 0b00001000,
        Down = 0b00000100,
        Left = 0b00000010,
        Right = 0b00000001
    };
    enum AttackMask: uint8_t {
        Light = 0b00001000,
        Medium = 0b00000100,
        Heavy = 0b00000010,
        Aerial = 0b00000001
    };

    struct Input {
        uint8_t directionHold {0};
        uint8_t directionPress {0};
        uint8_t directionRelease {0};

    	uint8_t attackHold {0};
        uint8_t attackPress {0};
        uint8_t attackRelease {0};
    };

    InputManager();
    ~InputManager();

    void buildInputList();

private:
    std::list<Input> m_inputList {};
    std::unordered_map<Action, KeyboardKey> m_keybinds {
        { Action::Up_Input, KEY_W },
        { Action::Down_Input, KEY_S },
        { Action::Left_Input, KEY_A },
        { Action::Right_Input, KEY_D },
        { Action::Light_Input, KEY_I },
        { Action::Medium_Input, KEY_O },
        { Action::Heavy_Input, KEY_P },
    };

	void getPreviousFrameInputs(Input& currentFrame, Input& previousFrame);
    void getHold(Input& input);
    void getPress(Input& input);
    void getRelease(Input& input);

    void sanitizeInputs(Input& input);
    void removeInvalidDirections(Input& input, DirectionMask command1, DirectionMask command2);
};

#endif
