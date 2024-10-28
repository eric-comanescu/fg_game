#include "../include/Input.h"

#include <vector>
// #include <iostream>

#include "../include/raylib.h"
#include "../include/StateMachine.h"

InputManager::InputManager() {
	// std::cout << "Test\n";
}

InputManager::~InputManager() {

}

InputManager::Input InputManager::getInput() {
	std::vector<KeyboardKey> keysPressed {};

	for (const auto& keybind : m_player1Keybinds) {
		// std::cout << std::get<0>(keybind) << " + " << std::get<1>(keybind) << '\n';
	}

	return {InputManager::MotionInputs::NONE, KEY_W, InputManager::Directions::UpNeutral};
}
