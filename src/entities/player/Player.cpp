#include "../../../include/Player.h"

#include <list>
#include <iostream>

#include "../../../include/raylib.h"
#include "../../../include/Input.h"

Player::Player() {

}

Player::~Player() {

}

void Player::handleMovement(float dt) {
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	const std::list<InputManager::Input>& inputs { m_inputManager.getInputList() };

	if ((inputs.back().directionHold & LEFT_BITMASK) > 0) {
		m_position.x -= 200 * dt;
	}

	if ((inputs.back().directionHold & RIGHT_BITMASK) > 0) {
		m_position.x += 200 * dt;
	}
}

void Player::update(float dt) {
	m_inputManager.update(dt);
	handleMovement(dt);
}

void Player::render() {
	// Temporary, for testing
	DrawRectangle(m_position.x, m_position.y, 50, 90, BLUE);
}
