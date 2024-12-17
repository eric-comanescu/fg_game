#include "../../../include/Player.h"

#include <list>
#include <iostream>
#include <typeinfo>
#include <algorithm>

#include "../../../include/raylib.h"
#include "../../../include/IdleState.h"
#include "../../../include/ForwardWalkState.h"
#include "../../../include/BackwardsWalkState.h"
#include "../../../include/CrouchState.h"
#include "../../../include/CrouchBlockState.h"
#include "../../../include/AttackState.h"
#include "../../../include/Input.h"
#include "../../../include/Hitbox.h"
#include "../../../include/GameEntity.h"

Player::Player(Vector2 pos, Vector2 dimensions, bool isP1, Hitbox hitboxOffsets)
	: m_isP1{isP1} {
	m_stateMachine.add(new ForwardWalkState(this));
	m_stateMachine.add(new BackwardsWalkState(this));
	m_stateMachine.add(new CrouchState(this));
	m_stateMachine.add(new CrouchBlockState(this));
	m_stateMachine.add(new AttackState(this));
	m_stateMachine.add(new IdleState(this));

	m_stateMachine.change(StateName::Player_Idle_State, nullptr);

	m_attacks.push_back(new Attack(this, {0b00001000}, 9, Attack::AttackStrength::Low, false, 0));
	m_attacks.push_back(new Attack(this, {0b00001000}, 9, Attack::AttackStrength::Low, true, 0));

	std::sort(m_attacks.begin(), m_attacks.end(), [](Attack* a, Attack* b) {
		return a->m_priority < b->m_priority;
	});

	m_position = pos;
	m_prevPosition = pos;
	m_dimensions = dimensions;

	if (m_isP1)
		m_inputManager.m_keybinds = {
			{InputManager::Action::Up_Input, KEY_W},
			{InputManager::Action::Down_Input, KEY_S},
			{InputManager::Action::Left_Input, KEY_A},
			{InputManager::Action::Right_Input, KEY_D},
			{InputManager::Action::Light_Input, KEY_Y},
			{InputManager::Action::Medium_Input, KEY_U},
			{InputManager::Action::Heavy_Input, KEY_I},
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
	
	m_hurtboxOffsets = hitboxOffsets;
	m_hurtbox.set(
		m_position.x + hitboxOffsets.position().x,
		m_position.y + hitboxOffsets.position().y,
		m_dimensions.x + hitboxOffsets.dimensions().x,
		m_dimensions.y + hitboxOffsets.dimensions().y
	);
}

Player::~Player() {
	for (auto& attack : m_attacks) {
		delete attack;
	}
}

void Player::update(float dt) {
	m_stateMachine.update(dt);

	m_hurtbox.set(
		m_position.x + m_hurtboxOffsets.position().x,
		m_position.y + m_hurtboxOffsets.position().y,
		m_dimensions.x + m_hurtboxOffsets.dimensions().x,
		m_dimensions.y + m_hurtboxOffsets.dimensions().y
	);
}

void Player::render() {
	m_stateMachine.render();

	DrawRectangle(m_position.x, m_position.y, m_dimensions.x, m_dimensions.y, BLUE);

	if (facing == Direction::Right)
		DrawRectangle(m_position.x + 30, m_position.y, 20, 90, YELLOW);
	else
		DrawRectangle(m_position.x, m_position.y, 20, 90, YELLOW);

	m_hurtbox.render();
}

bool Player::didCollideWith(const Hitbox& target) {
	return m_hurtbox.didCollide(target);
}

const Hitbox& Player::hitbox() {
	return m_hurtbox;
}

void Player::onCollision(GameEntity* collider) {
	if (collider == this) {
		return;
	}

	// set collider position outside of collidee
	m_position = m_prevPosition;
}
