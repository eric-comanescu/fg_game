#include "../../../include/Player.h"

#include <list>
#include <iostream>

#include "../../../include/raylib.h"
#include "../../../include/IdleState.h"
#include "../../../include/ForwardWalkState.h"
#include "../../../include/Input.h"

Player::Player(Vector2 pos, bool isP1)
	: m_isP1{isP1} {
	m_stateMachine.add(new ForwardWalkState(this));
	m_stateMachine.add(new IdleState(this));

	m_position = pos;

	if (m_isP1)
		m_inputManager.m_keybinds = {
			{InputManager::Action::Up_Input, KEY_W},
			{InputManager::Action::Down_Input, KEY_S},
			{InputManager::Action::Left_Input, KEY_A},
			{InputManager::Action::Right_Input, KEY_D},
			{InputManager::Action::Light_Input, KEY_I},
			{InputManager::Action::Medium_Input, KEY_O},
			{InputManager::Action::Heavy_Input, KEY_P},
		};
	else
		m_inputManager.m_keybinds = {
			{InputManager::Action::Up_Input, KEY_UP},
			{InputManager::Action::Down_Input, KEY_DOWN},
			{InputManager::Action::Left_Input, KEY_LEFT},
			{InputManager::Action::Right_Input, KEY_RIGHT},
			{InputManager::Action::Light_Input, KEY_LEFT_BRACKET},
			{InputManager::Action::Medium_Input, KEY_RIGHT_BRACKET},
			{InputManager::Action::Heavy_Input, KEY_BACKSLASH},
		};
}

Player::~Player() {

}

void Player::update(float dt) {
	m_stateMachine.update(dt);

	std::cout << m_isP1 << '\n';
}

void Player::render() {
	// Temporary, for testing
	// m_inputManager.debugRender();

	m_stateMachine.render();

	DrawRectangle(m_position.x, m_position.y, 50, 90, BLUE);

	if (facing == Direction::Right)
		DrawRectangle(m_position.x + 30, m_position.y, 20, 90, RED);
	else
		DrawRectangle(m_position.x, m_position.y, 20, 90, RED);
}
