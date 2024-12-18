#include "../../../include/BackwardsWalkState.h"

#include <list>

#include "../../../include/Player.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"

BackwardsWalkState::BackwardsWalkState(Player* player)
	: State()
	, m_player {player}
{}

BackwardsWalkState::~BackwardsWalkState() {

}

void BackwardsWalkState::enter(void* params = nullptr) {
	m_player->m_isBlocking = true;
	m_player->m_hurtboxOffsets.position() = Player::BWALK_HURTBOX_OFFSETS;
	m_player->m_hurtboxOffsets.dimensions() = Player::BWALK_HURTBOX_DIMENSIONS;
}

void BackwardsWalkState::exit() {
	m_player->m_isBlocking = false;
}

void BackwardsWalkState::update(float dt) {
	m_player->m_inputManager.update(dt);

	handleMovement(dt);

	checkTransition();
}

void BackwardsWalkState::render() {
	if (m_player->m_isP1)
		DrawText("P1 Backwards Walk", 0, 20, 24, WHITE);
	else
		DrawText("P2 Backwards Walk", 0, 40, 24, WHITE);
}

StateName BackwardsWalkState::name() {
	return m_name;
}

void BackwardsWalkState::checkTransition() {
	constexpr uint8_t DOWN_BITMASK = 0b00000100;
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;

	const uint8_t directionHold { m_player->m_inputManager.getInputList().back().directionHold };
	const uint8_t attackPress { m_player->m_inputManager.getInputList().back().attackPress };

	// TODO: Check idle for more to do
	if ((attackPress & LATTACK_BITMASK) != 0) {
		if ((directionHold & DOWN_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
		}
		else {
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[1]);
		}
	}

	if (m_player->facing == Direction::Right) {
		// TODO: Add check for crouch block
		if ((directionHold & LEFT_BITMASK) == 0) {
			if ((directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
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
		// TODO: Add check for crouch block
		if ((directionHold & RIGHT_BITMASK) == 0) {
			if ((directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
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

void BackwardsWalkState::handleMovement(float dt) {
	if (m_player->facing == Direction::Right) {
		m_player->m_position.x = m_player->m_hurtbox.position().x - 60 * dt >= 0 ? m_player->m_position.x - 60 * dt : -25;
	}
	else {
		m_player->m_position.x = m_player->m_hurtbox.position().x + 60 * dt + m_player->m_hurtbox.dimensions().x <= 320 ?
			m_player->m_position.x + 60 * dt : 245; 
	}
}
