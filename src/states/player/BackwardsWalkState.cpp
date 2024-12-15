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
	constexpr uint8_t LEFT_MOVEMENT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_MOVEMENT_BITMASK = 0b00000001;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	// if ((inputs.back().directionHold & MOVEMENT_BITMASKS) == 0) {
	// 	m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
	// }

	if (m_player->facing == Direction::Right) {
		if ((inputs.back().directionHold & LEFT_MOVEMENT_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
		}
	}
	else {
		if ((inputs.back().directionHold & RIGHT_MOVEMENT_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
		}
	}
}

void BackwardsWalkState::handleMovement(float dt) {
	if (m_player->facing == Direction::Right)
		m_player->m_nextPosition.x -= 100 * dt;
	else
		m_player->m_nextPosition.x += 100 * dt;
}
