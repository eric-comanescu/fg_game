#include "../include/Input.h"

#include <iostream>
#include <cassert>
#include <sstream>
#include <bitset>
#include <list>

#include "../include/raylib.h"

InputManager::InputManager() {
	m_inputList.push_back(Input());
}

InputManager::~InputManager() {

}

void InputManager::update(float dt) {
	constexpr float fixedFrameTime = 1 / 60;
	if (m_timeSinceLastInputBuild += dt; m_timeSinceLastInputBuild >= fixedFrameTime) {
		m_timeSinceLastInputBuild = 0;

		buildInputList();
	}
}

void InputManager::debugRender() {
	Input i = m_inputList.back();
	std::stringstream ss {};
	ss << "Attack Hold: " << std::bitset<8>(i.attackHold) << "\n";
	ss << "Attack Press: " << std::bitset<8>(i.attackPress) << "\n";
	ss << "Attack Release: " << std::bitset<8>(i.attackRelease) << "\n";
	ss << "Direction Hold: " << std::bitset<8>(i.directionHold) << "\n";
	ss << "Direction Press: " << std::bitset<8>(i.directionPress) << "\n";
	ss << "Direction Release: " << std::bitset<8>(i.directionRelease) << "\n";

	DrawText(ss.str().c_str(), 0, 24, 16, WHITE);
}

void InputManager::buildInputList() {
	Input previousInput = m_inputList.back();
	Input currentInput {};

    // to hold input for 15 frames, remove up to 15th element
    if (m_inputList.size() > 15) {
        m_inputList.pop_front();
    }

    // catch if input queue somehow contains more than 14 frames (called buildInputQueue twice somewhere)
    assert(m_inputList.size() <= 15 && "buildInputQueue called twice somewhere.");

	// Set bits for previous frame
	getPreviousFrameInputs(currentInput, previousInput);

    // Get Hold
    getHold(currentInput);

	// Sanitize inputs after hold
    sanitizeInputs(currentInput);

    // Get Press
    getPress(currentInput);

    // Get Release
    getRelease(currentInput);

	// Adds current frame's inputs to list
	m_inputList.push_back(currentInput);
}

void InputManager::getPreviousFrameInputs(Input& currentFrame, Input& previousFrame) {
	constexpr uint8_t lower4BitsMask = 0b00001111;

	currentFrame.attackHold = currentFrame.attackHold | (previousFrame.attackHold & lower4BitsMask);
	currentFrame.attackPress = currentFrame.attackPress | (previousFrame.attackPress & lower4BitsMask);
	currentFrame.attackRelease = currentFrame.attackRelease | (previousFrame.attackRelease & lower4BitsMask);

	currentFrame.directionHold = currentFrame.directionHold | (previousFrame.directionHold & lower4BitsMask);
	currentFrame.directionPress = currentFrame.directionPress | (previousFrame.directionPress & lower4BitsMask);
	currentFrame.directionRelease = currentFrame.directionRelease | (previousFrame.directionRelease & lower4BitsMask);
}

void InputManager::getHold(Input& input) {
    input.directionHold <<= 4;
    input.attackHold <<= 4;

    if (IsKeyDown(m_keybinds[Action::Up_Input])) {
        input.directionHold |= DirectionMask::Up;
    }

    if (IsKeyDown(m_keybinds[Action::Down_Input])) {
        input.directionHold |= DirectionMask::Down;
    }

    if (IsKeyDown(m_keybinds[Action::Left_Input])) {
        input.directionHold |= DirectionMask::Left;
    }

    if (IsKeyDown(m_keybinds[Action::Right_Input])) {
        input.directionHold |= DirectionMask::Right;
    }

    if (IsKeyDown(m_keybinds[Action::Light_Input])) {
        input.attackHold |= AttackMask::Light;
    }

    if (IsKeyDown(m_keybinds[Action::Medium_Input])) {
        input.attackHold |= AttackMask::Medium;
    }

    if (IsKeyDown(m_keybinds[Action::Heavy_Input])) {
        input.attackHold |= AttackMask::Heavy;
    }
}

void InputManager::getPress(Input& input) {
    input.directionPress <<= 4;
    input.attackPress <<= 4;

    if (IsKeyPressed(m_keybinds[Action::Up_Input])) {
        input.directionPress |= DirectionMask::Up;
    }

    if (IsKeyPressed(m_keybinds[Action::Down_Input])) {
        input.directionPress |= DirectionMask::Down;
    }

    if (IsKeyPressed(m_keybinds[Action::Left_Input])) {
        input.directionPress |= DirectionMask::Left;
    }

    if (IsKeyPressed(m_keybinds[Action::Right_Input])) {
        input.directionPress |= DirectionMask::Right;
    }

    if (IsKeyPressed(m_keybinds[Action::Light_Input])) {
        input.attackPress |= AttackMask::Light;
    }

    if (IsKeyPressed(m_keybinds[Action::Medium_Input])) {
        input.attackPress |= AttackMask::Medium;
    }

    if (IsKeyPressed(m_keybinds[Action::Heavy_Input])) {
        input.attackPress |= AttackMask::Heavy;
    }
}

void InputManager::getRelease(Input& input) {
	constexpr uint8_t FIRST_4_BITS_MASK = 0b11110000;

	input.attackRelease <<= 4;
	input.directionRelease <<= 4;

	if (((input.directionHold & FIRST_4_BITS_MASK) >> 4) != (input.directionHold & ~FIRST_4_BITS_MASK)) {
		std::cout << std::bitset<4>((input.directionHold & FIRST_4_BITS_MASK) >> 4) << '\n';
		std::cout << std::bitset<4>((input.directionHold & ~FIRST_4_BITS_MASK)) << '\n';

		// TODO: Working on this
		std::cout << 
		input.directionRelease |= ((input.directionHold >> 4) & ~(input.directionHold & ~FIRST_4_BITS_MASK));
	}

	if (!(input.attackHold & FIRST_4_BITS_MASK) == (input.attackHold & ~FIRST_4_BITS_MASK) && (input.attackHold & FIRST_4_BITS_MASK) != 0) {
		input.attackRelease |= ((input.attackHold >> 4) & ~(input.attackHold & ~FIRST_4_BITS_MASK));
	}

	// if (IsKeyReleased(m_keybinds[Action::Up_Input])) {
	// 	input.directionRelease |= DirectionMask::Up;
	// }

    // if (IsKeyReleased(m_keybinds[Action::Down_Input])) {
    //     input.directionRelease |= DirectionMask::Down;
    // }

    // if (IsKeyReleased(m_keybinds[Action::Left_Input])) {
    //     input.directionRelease |= DirectionMask::Left;
    // }

    // if (IsKeyReleased(m_keybinds[Action::Right_Input])) {
    //     input.directionRelease |= DirectionMask::Right;
    // }

    // if (IsKeyReleased(m_keybinds[Action::Light_Input])) {
    //     input.attackRelease |= AttackMask::Light;
    // }

    // if (IsKeyReleased(m_keybinds[Action::Medium_Input])) {
    //     input.attackRelease |= AttackMask::Medium;
    // }

    // if (IsKeyReleased(m_keybinds[Action::Heavy_Input])) {
    //     input.attackRelease |= AttackMask::Heavy;
    // }


}

void InputManager::sanitizeInputs(Input& input) {
	removeInvalidDirections(input, DirectionMask::Up, DirectionMask::Down);
	removeInvalidDirections(input, DirectionMask::Left, DirectionMask::Right);
}

void InputManager::removeInvalidDirections(Input& input, DirectionMask command1, DirectionMask command2) {
    if (((input.directionHold & (command1 | command2)) ^ (command1 | command2)) == 0 && (input.directionHold & 0b00001111) != 0) {
        input.directionHold &= ~(command1 | command2);
    }
}
