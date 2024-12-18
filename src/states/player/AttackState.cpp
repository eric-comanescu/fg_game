#include "../../../include/AttackState.h"

#include <sstream>
#include <iostream>

#include "../../../include/Player.h"
#include "../../../include/Attack.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"
#include "../../../include/raylib.h"

AttackState::AttackState(Player* player)
	: State()
	, m_player {player} {

}

AttackState::~AttackState() {

}

void AttackState::enter(void* params) {
	m_attack = reinterpret_cast<Attack*>(params);
	m_duration = m_attack->m_duration;

	m_player->m_activeAttack = m_attack;

	m_canCancel = false;

	if (m_attack->m_isLow) {
		m_player->m_hurtboxOffsets.position() = Player::CROUCH_HURTBOX_OFFSETS;
		m_player->m_hurtboxOffsets.dimensions() = Player::CROUCH_HURTBOX_DIMENSIONS;
	}
	else {
		m_player->m_hurtboxOffsets.position() = Player::IDLE_HURTBOX_OFFSETS;
		m_player->m_hurtboxOffsets.dimensions() = Player::IDLE_HURTBOX_DIMENSIONS;
	}

	m_player->renderPriority = 1;
}

void AttackState::exit() {
	m_player->m_hurtboxOffsets.dimensions() = Player::STANDING_DIMENSIONS;

	m_player->m_activeAttack = nullptr;
	m_player->m_activeHitbox = nullptr;

	m_canCancel = false;

	m_attack->m_animation->reset();

	if (m_attack->m_isLow)
		m_player->m_hurtboxOffsets.position().y = 10;

	m_player->renderPriority = 0;
}

void AttackState::update(float dt) {
	m_player->m_inputManager.update(dt);

	if (m_player->facing == Direction::Right) {
		m_attack->m_hitbox.set(
			m_player->m_hurtbox.position().x + m_attack->m_hitboxOffset.position().x,
			m_player->m_hurtbox.position().y + m_attack->m_hitboxOffset.position().y,
			m_attack->m_hitboxOffset.dimensions().x,
			m_attack->m_hitboxOffset.dimensions().y
		);
	}
	else {
		m_attack->m_hitbox.set(
			m_player->m_hurtbox.position().x - m_attack->m_hitboxOffset.dimensions().x + m_player->m_hurtbox.dimensions().x - m_attack->m_hitboxOffset.dimensions().x,
			m_player->m_hurtbox.position().y + m_attack->m_hitboxOffset.position().y,
			m_attack->m_hitboxOffset.dimensions().x,
			m_attack->m_hitboxOffset.dimensions().y
		);
	}

	if (m_player->m_pushBlockDistance > 0) {
		m_player->m_pushBlockDistance -= 1.0f;

		if (m_player->facing == Direction::Right) {
			m_player->m_position.x -= 1.0f;
		}
		else {
			m_player->m_position.x += 1.0f;
		}
	}

	if (m_attack->m_hitbox.isConsumed) {
		m_canCancel = true;
	}

	if (m_attack->m_animation->currentFrame() == 2) {
		m_attack->m_hitbox.isActive = true;
		m_player->m_activeHitbox = &m_attack->m_hitbox;
	}
	else {
		m_attack->m_hitbox.isActive = false;
		m_attack->m_hitbox.isConsumed = false;
		m_player->m_activeHitbox = nullptr;
	}

	m_attack->m_animation->update(dt);

	m_duration -= dt;

	checkTranstions();
}

void AttackState::render() {
	if (m_player->facing == Direction::Right)
		DrawTexturePro(
			m_player->m_sprites,
			m_attack->m_animation->currentSprite(),
			(Rectangle){m_player->m_position.x, m_player->m_position.y, m_player->m_dimensions.x, m_player->m_dimensions.y},
			{0.0f, 0.0f},
			0.0f,
			WHITE);
	else
		DrawTexturePro(
			m_player->m_sprites,
			m_attack->m_animation->currentSpriteFlipped(),
			(Rectangle){m_player->m_position.x, m_player->m_position.y, m_player->m_dimensions.x, m_player->m_dimensions.y},
			{0.0f, 0.0f},
			0.0f,
			WHITE);

	// m_attack->m_hitbox.render();
}

StateName AttackState::name() {
	return m_name;
}

void AttackState::checkTranstions() {
	const InputManager::Input& input { m_player->m_inputManager.getInputList().back() };

	// Checking for valid attack cancels if hit was consumed
	if (m_canCancel) {
		constexpr uint8_t DOWN_BITMASK = 0b00000100;

		constexpr uint8_t LATTACK_BITMASK = 0b00001000;

		if ((input.attackPress & LATTACK_BITMASK) != 0) {
			if ((input.directionHold & DOWN_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[1]);
			}
			else {
				m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
			}
		}
	}

	// TODO: Check if consumed to allow cancels
	if (m_duration > 0)
		return;
	
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;
	constexpr uint8_t DOWN_BITMASK = 0b00000100;

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;


	// TODO: More complex (check idle state)
	if ((input.attackPress & LATTACK_BITMASK) != 0) {
		if ((input.directionHold & DOWN_BITMASK) != 0)
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[1]);
		else
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
	}

	if (m_player->facing == Direction::Right) {
		if ((input.directionHold & DOWN_BITMASK) == 0) {
			if ((input.directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if((input.directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add else if for jump (UP_BITMASK)
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((input.directionHold & LEFT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouch_Blocking_State, nullptr);
		}
		else {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
	else {
		if ((input.directionHold & DOWN_BITMASK) == 0) {
			if ((input.directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if((input.directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add else if for jump (UP_BITMASK)
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((input.directionHold & RIGHT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouch_Blocking_State, nullptr);
		}
		else {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
}
