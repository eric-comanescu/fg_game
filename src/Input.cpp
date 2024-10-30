#include "../include/Input.h"

#include <vector>
#include <cassert>
// #include <iostream>

#include "../include/raylib.h"

InputManager::InputManager() {
	// std::cout << "Test\n";
}

InputManager::~InputManager() {

}

void InputManager::buildInputQueue() {
	// to hold input for 15 frames, remove up to 15th element
	if (m_inputQueue.size() >= 15) {
		m_inputQueue.pop();
	}

	// catch if input queue somehow contains more than 14 frames (called buildInputQueue twice somewhere)
	assert(m_inputQueue.size() <= 14 && "buildInputQueue called twice somewhere.");

	Input input = m_inputQueue.back();

	// Get Hold
	getHold(input);

	// Release algo: ~((01100100 >> 4) & (00001111 & 01100100)) & (01100100 >> 4)
}

void InputManager::getHold(Input& input) {
	input.directionHold <<= 4;
	input.attackHold <<= 4;

	// TODO: do more here
	if (IsKeyDown(m_keybinds[Direction::Up])) {
		input.directionHold |= m_keybinds[Direction::Up];
	}

	if (IsKeyDown(m_keybinds[Direction::Down])) {
		input.directionHold |= m_keybinds[Direction::Down];
	}

	if (IsKeyDown(m_keybinds[Direction::Left])) {
		input.directionHold |= m_keybinds[Direction::Left];
	}

	if (IsKeyDown(m_keybinds[Direction::Right])) {
		input.directionHold |= m_keybinds[Direction::Right];
	}
}

void InputManager::removeInvalidInputs(Input& input, Direction command1, Direction command2) {
	if ((input.directionHold & (command1 | command2)) ^ (command1 | command2) == 0 && input.directionHold & 0b00001111 != 0) {
		input.directionHold &= ~(command1 | command2);
	}
}
