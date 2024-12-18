#include "../../../include/ForwardWalkState.h"

#include <iostream>
#include <list>
#include <bitset>

#include "../../../include/Player.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"

ForwardWalkState::ForwardWalkState(Player* player)
	: State()
	, m_player {player}
{}

ForwardWalkState::~ForwardWalkState() {

}

void ForwardWalkState::enter(void* params = nullptr) {
	m_player->m_hurtboxOffsets.position().y = 10;
}

void ForwardWalkState::exit() {

}

void ForwardWalkState::update(float dt) {
	m_player->m_inputManager.update(dt);

	handleMovement(dt);

	checkTransitions();
}

void ForwardWalkState::render() {
	if (m_player->m_isP1)
		DrawText("P1 Forward Walk", 0, 20, 24, WHITE);
	else
		DrawText("P2 Forward Walk", 0, 40, 24, WHITE);
}

StateName ForwardWalkState::name() {
	return m_name;
}

void ForwardWalkState::checkTransitions() {
	constexpr uint8_t DOWN_BITMASK = 0b00000100;
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;

	const uint8_t directionHold { m_player->m_inputManager.getInputList().back().directionHold };
	const uint8_t attackPress {m_player->m_inputManager.getInputList().back().attackPress};

	// TODO: More complex (check idle state)
	if ((attackPress & LATTACK_BITMASK) != 0) {
		m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
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

void ForwardWalkState::handleMovement(float dt) {
	if (m_player->facing == Direction::Right)
		// m_player->m_position.x = m_player->m_hurtbox.position().x + 100 * dt <= 320 ? m_player->m_hurtbox.position().x + 100 * dt : 320;
		m_player->m_position.x = m_player->m_hurtbox.position().x + 100 * dt <= 320 ? m_player->m_position.x + 100 * dt : 245;
	else
		m_player->m_position.x = m_player->m_hurtbox.position().x - 100 * dt >= 0 ?
			m_player->m_position.x - 100 * dt : 25;
}
