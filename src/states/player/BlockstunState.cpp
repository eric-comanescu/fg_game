#include "../../../include/BlockstunState.h"

#include <cassert>
#include <iostream>

#include "../../../include/Player.h"
#include "../../../include/Attack.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"
#include "../../../include/raylib.h"

BlockstunState::BlockstunState(Player* player)
	: State()
	, m_player {player} {

}

BlockstunState::~BlockstunState() {

}

void BlockstunState::enter(void* params) {
	m_player->m_isBlocking = true;

	// reinterpret cast to attack strength
	assert(params != nullptr && "Don't pass in nullptr as params to BlockstunState");
	Attack::AttackStrength* attackStrength = reinterpret_cast<Attack::AttackStrength*>(params);

	switch (*attackStrength) {
		case Attack::AttackStrength::Low:
			m_duration = 8.0f / 60.0f;
			break;

		case Attack::AttackStrength::Medium:
			m_duration = 14.0f / 60.0f;
			break;

		case Attack::AttackStrength::Strong:
			m_duration = 23.0f / 60.0f;
			break;
	};

	if (m_player->m_isCrouching) {
		m_player->m_hurtboxOffsets.position() = Player::CROUCH_HURTBOX_OFFSETS;
		m_player->m_hurtboxOffsets.dimensions() = Player::CROUCH_HURTBOX_DIMENSIONS;
	}
	else {
		m_player->m_hurtboxOffsets.position() = Player::CROUCH_HURTBOX_OFFSETS;
		m_player->m_hurtboxOffsets.dimensions() = Player::CROUCH_HURTBOX_DIMENSIONS;
	}
}

void BlockstunState::exit() {
	m_player->m_isBlocking = false;
	if (!m_player->m_isCrouching) {
		m_player->m_hurtboxOffsets.dimensions() = Player::STANDING_DIMENSIONS;
		m_player->m_hurtboxOffsets.position().y = 10;
	}
}

void BlockstunState::update(float dt) {
	m_player->m_inputManager.update(dt);

	m_duration -= dt;

	if (m_player->m_pushBlockDistance > 0) {
		m_player->m_pushBlockDistance -= 1.0f;

		if (m_player->facing == Direction::Right) {
			m_player->m_position.x -= 1.0f;
		}
		else {
			m_player->m_position.x += 1.0f;
		}
	}

	checkTransitions();
}

void BlockstunState::render() {
	if (m_player->facing == Direction::Right) {
		DrawText("P1 Blockstun", 0, 20, 24, WHITE);
	}
	else {
		DrawText("P2 Blockstun", 0, 40, 24, WHITE);
	}
}

StateName BlockstunState::name() {
	return m_name;
}

void BlockstunState::checkTransitions() {
	if (m_duration > 0)
		return;

	// do the rest here
	constexpr uint8_t DOWN_BITMASK = 0b00000100;
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;

	const uint8_t directionHold { m_player->m_inputManager.getInputList().back().directionHold };
	const uint8_t attackPress {m_player->m_inputManager.getInputList().back().attackPress};

	// TODO: More complex (check idle state)
	if ((attackPress & LATTACK_BITMASK) != 0) {
		if ((directionHold & DOWN_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
		}
		else {
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[1]);
		}
	}

	if (m_player->facing == Direction::Right) {
		if ((directionHold & RIGHT_BITMASK) == 0) {
			// TODO: Add check for crouch block
			if ((directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((directionHold & DOWN_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
	else {
		if ((directionHold & LEFT_BITMASK) == 0) {
			// TODO: Add check for crouch block
			if ((directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((directionHold & DOWN_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
}
