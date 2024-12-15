#include "../../../include/Player.h"

#include <list>
#include <iostream>

#include "../../../include/raylib.h"
#include "../../../include/IdleState.h"
#include "../../../include/ForwardWalkState.h"
#include "../../../include/BackwardsWalkState.h"
#include "../../../include/Input.h"
#include "../../../include/Hitbox.h"

Player::Player(Vector2 pos, Vector2 dimensions, bool isP1, Hitbox hitboxOffsets)
	: m_isP1{isP1} {
	m_stateMachine.add(new ForwardWalkState(this));
	m_stateMachine.add(new BackwardsWalkState(this));
	m_stateMachine.add(new IdleState(this));

	m_position = pos;
	m_dimensions = dimensions;

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
	
	m_hitboxOffsets = hitboxOffsets;
	m_hitbox.set(
		m_position.x + hitboxOffsets.position().x,
		m_position.y + hitboxOffsets.position().y,
		m_dimensions.x + hitboxOffsets.dimensions().x,
		m_dimensions.y + hitboxOffsets.dimensions().y
	);
}

Player::~Player() {

}

void Player::update(float dt) {
	m_stateMachine.update(dt);

	m_hitbox.set(
		m_position.x + m_hitboxOffsets.position().x,
		m_position.y + m_hitboxOffsets.position().y,
		m_dimensions.x + m_hitboxOffsets.dimensions().x,
		m_dimensions.y + m_hitboxOffsets.dimensions().y
	);
}

void Player::render() {
	// Temporary, for testing
	// m_inputManager.debugRender();

	m_stateMachine.render();

	DrawRectangle(m_position.x, m_position.y, m_dimensions.x, m_dimensions.y, BLUE);

	// if (facing == Direction::Right)
	// 	DrawRectangle(m_position.x + 30, m_position.y, 20, 90, RED);
	// else
	// 	DrawRectangle(m_position.x, m_position.y, 20, 90, RED);

	m_hitbox.render();
}

bool Player::didCollideWith(const Hitbox& target) {
	return m_hitbox.didCollide(target);
}

const Hitbox& Player::hitbox() {
	return m_hitbox;
}
