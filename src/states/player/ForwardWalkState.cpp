#include "../../../include/ForwardWalkState.h"

#include <iostream>
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
	constexpr uint8_t MOVEMENT_BITMASKS = 0b00000011;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	if ((inputs.back().directionHold & MOVEMENT_BITMASKS) == 0) {
		m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
	}
}

void ForwardWalkState::handleMovement(float dt) {
	if (m_player->facing == Direction::Right)
		m_player->m_position.x += 200 * dt;
	else
		m_player->m_position.x -= 200 * dt;
}
