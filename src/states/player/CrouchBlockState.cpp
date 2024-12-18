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
	m_player->m_isBlocking = true;
	m_player->m_isCrouching = true;

	m_player->m_hurtboxOffsets.position() = Player::CROUCH_HURTBOX_OFFSETS;
	m_player->m_hurtboxOffsets.dimensions() = Player::CROUCH_HURTBOX_DIMENSIONS;
}

void CrouchBlockState::exit() {
	m_player->m_hurtboxOffsets.position().y = 10;
	m_player->m_hurtboxOffsets.dimensions() = Player::STANDING_DIMENSIONS;
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

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;

	const uint8_t directionHold { m_player->m_inputManager.getInputList().back().directionHold };
	const uint8_t attackPress { m_player->m_inputManager.getInputList().back().attackPress };

	// TODO: Check idle state for more to do
	if ((attackPress & LATTACK_BITMASK) != 0) {
		if ((directionHold & DOWN_BITMASK) != 0)
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[1]);
		else
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
	}

	if (m_player->facing == Direction::Right) {
		if ((directionHold & DOWN_BITMASK) == 0) {
			if ((directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if ((directionHold & LEFT_BITMASK) != 0) {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add jump detection
			else {
				m_player->m_isCrouching = false;
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
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if ((directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add jump detection
			else {
				m_player->m_isCrouching = false;
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((directionHold & RIGHT_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}

	}
}
