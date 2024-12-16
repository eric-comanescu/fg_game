#include "../../../include/CrouchBlockState.h"

#include "../../../include/Player.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"
#include "../../../include/raylib.h"

CrouchBlockState::CrouchBlockState(Player* player)
	: State()
	, m_player {player} {

}

CrouchBlockState::~CrouchBlockState() {

}

void CrouchBlockState::enter(void* params) {
	m_originalPos = m_player->m_position;
	m_originalDim = m_player->m_dimensions;
	m_player->m_isBlocking = true;

	m_player->m_position.y += 40;
	m_player->m_dimensions.y -= 40;
}

void CrouchBlockState::exit() {
	m_player->m_position = m_originalPos;
	m_player->m_dimensions = m_originalDim;
	m_player->m_isBlocking = false;
}

void CrouchBlockState::update(float dt) {
	m_player->m_inputManager.update(dt);

	checkTransitions();
}

void CrouchBlockState::render() {
	if (m_player->facing == Direction::Right) 
		DrawText("P1 Crouch Block", 0, 20, 24, WHITE);
	else
		DrawText("P2 Crouch Block", 0, 40, 24, WHITE);
}

StateName CrouchBlockState::name() {
	return m_name;
}

void CrouchBlockState::checkTransitions() {
	constexpr uint8_t DOWN_BITMASK = 0b00000100;
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	const uint8_t directionHold { m_player->m_inputManager.getInputList().back().directionHold };

	if (m_player->facing == Direction::Right) {
		if ((directionHold & DOWN_BITMASK) == 0) {
			if ((directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if ((directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add jump detection
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((directionHold & LEFT_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
	else {
		if ((directionHold & DOWN_BITMASK) == 0) {
			if ((directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if ((directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add jump detection
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((directionHold & RIGHT_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}

	}
}
