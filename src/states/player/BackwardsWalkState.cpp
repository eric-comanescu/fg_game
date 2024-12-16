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

}

void BackwardsWalkState::exit() {

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

	const uint8_t directionHold { m_player->m_inputManager.getInputList().back().directionHold };

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
	if (m_player->facing == Direction::Right)
		m_player->m_position.x -= 60 * dt;
	else
		m_player->m_position.x += 60 * dt;
}
