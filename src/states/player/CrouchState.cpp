#include "../../../include/CrouchState.h"

#include <list>
#include <iostream>

#include "../../../include/Player.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"
#include "../../../include/raylib.h"

CrouchState::CrouchState(Player* player)
	: State()
	, m_player {player} {

}

CrouchState::~CrouchState() {

}

void CrouchState::enter(void* params) {
	m_originalPos = m_player->m_position;
	m_player->m_isCrouching = true;

	m_player->m_position.y = Player::CROUCHING_POS;
	m_player->m_dimensions = Player::CROUCHING_DIMENSIONS;
}

void CrouchState::exit() {
	m_player->m_position.y = Player::STANDING_POS;
	m_player->m_dimensions = Player::STANDING_DIMENSIONS;
	m_player->m_isCrouching = false;
}

void CrouchState::update(float dt) {
	m_player->m_inputManager.update(dt);

	checkTransitions();
}

void CrouchState::render() {
	if (m_player->m_isP1)
		DrawText("P1 Crouch", 0, 20, 24, WHITE);
	else
		DrawText("P2 Crouch", 0, 40, 24, WHITE);
}

StateName CrouchState::name() {
	return m_name;
}

void CrouchState::checkTransitions() {
	constexpr uint8_t DOWN_BITMASK = 0b00000100;
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;

	const InputManager::Input& input { m_player->m_inputManager.getInputList().back() };

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
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if((input.directionHold & LEFT_BITMASK) != 0) {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add else if for jump (UP_BITMASK)
			else {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((input.directionHold & LEFT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouch_Blocking_State, nullptr);
		}
	}
	else {
		if ((input.directionHold & DOWN_BITMASK) == 0) {
			if ((input.directionHold & LEFT_BITMASK) != 0) {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if((input.directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add else if for jump (UP_BITMASK)
			else {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((input.directionHold & RIGHT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouch_Blocking_State, nullptr);
		}
	}
}
