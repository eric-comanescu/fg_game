#include "../include/Input.h"

#include <vector>

#include "../include/raylib.h"
#include "../include/StateMachine.h"

InputManager::InputManager() {

}

InputManager::~InputManager() {

}

InputManager::Input InputManager::getInput() {
	std::vector<KeyboardKey> keysPressed {};
	do {
		KeyboardKey keyPressed { static_cast<KeyboardKey>(GetKeyPressed()) };

	}
}
