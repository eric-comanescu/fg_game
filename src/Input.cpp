#include "../include/Input.h"

#include <cassert>
#include <queue>
#include <iostream>
#include <bitset>

#include "../include/raylib.h"

InputManager::InputManager() {
    // std::cout << "Test\n";
}

InputManager::~InputManager() {

}

void InputManager::buildInputList() {
	// Input previousInput = m_inputList.empty() ? Input() : m_inputList.back();

	Input previousInput;
	if (m_inputList.empty()) {
		previousInput = Input();
	}
	else {
		previousInput = m_inputList.back();
	}

	Input currentInput { 0, 0, 0, 0, 0, 0 };

	// Input currentInput = m_inputList.back();

    // to hold input for 15 frames, remove up to 15th element
    if (m_inputList.size() >= 15) {
        m_inputList.pop_front();
    }

    // catch if input queue somehow contains more than 14 frames (called buildInputQueue twice somewhere)
    assert(m_inputList.size() <= 14 && "buildInputQueue called twice somewhere.");

	// Set bits for previous frame
	// getPreviousFrameInputs(currentInput, previousInput);

    // Get Hold
    getHold(currentInput);

    // Get Press
    getPress(currentInput);

    // Get Release
    getRelease(currentInput);

    sanitizeInputs(currentInput);

	// Adds current frame's inputs to list
	m_inputList.push_back(currentInput);

	// std::cout << "Previous Frame: " << std::bitset<8>(previousInput.directionHold) << '\n';
	// std::cout << " Current Frame: " << std::bitset<8>(currentInput.directionHold) << '\n';
}

void InputManager::getPreviousFrameInputs(Input& currentFrame, Input& previousFrame) {
	currentFrame.attackHold |= previousFrame.attackHold << 4;
	currentFrame.attackPress |= previousFrame.attackPress << 4;
	currentFrame.attackRelease |= previousFrame.attackRelease << 4;

	currentFrame.directionHold |= previousFrame.directionHold << 4;
	currentFrame.directionPress |= previousFrame.directionPress << 4;
	currentFrame.directionRelease |= previousFrame.directionRelease << 4;
}

void InputManager::getHold(Input& input) {
    input.directionHold <<= 4;
    input.attackHold <<= 4;

    // TODO: do more here
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
		std::cout << "Oh no\n";
        input.attackHold |= AttackMask::Light;
    }

    if (IsKeyDown(m_keybinds[Action::Medium_Input])) {
		std::cout << "Oh no\n";
        input.attackHold |= AttackMask::Medium;
    }

    if (IsKeyDown(m_keybinds[Action::Heavy_Input])) {
		std::cout << "Oh no\n";
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
    input.directionRelease = (input.directionRelease << 4) | ((input.directionHold >> 4) ^ (input.directionHold & 0b00001111));
    input.attackRelease = (input.attackRelease << 4) | ((input.attackHold >> 4) ^ (input.attackHold & 0b00001111));
}

void InputManager::sanitizeInputs(Input& input) {

}

void InputManager::removeInvalidInputs(Input& input, DirectionMask command1, DirectionMask command2) {
    if (((input.directionHold & (command1 | command2)) ^ (command1 | command2)) == 0 && (input.directionHold & 0b00001111) != 0) {
        input.directionHold &= ~(command1 | command2);
    }
}
