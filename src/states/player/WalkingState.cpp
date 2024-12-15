#include "../../../include/WalkingState.h"

#include <iostream>
#include <bitset>

#include "../../../include/Player.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"

WalkingState::WalkingState(Player* player)
	: State {},
	m_player {player}
{}

WalkingState::~WalkingState() {

}

void WalkingState::enter(void* params = nullptr) {
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	if ((inputs.back().directionHold & LEFT_BITMASK) > 0) {
		m_walkingDirection = Direction::Left;
	}

	if ((inputs.back().directionHold & RIGHT_BITMASK) > 0) {
		m_walkingDirection = Direction::Right;
	}
}

void WalkingState::exit() {

}

void WalkingState::update(float dt) {
	m_player->m_inputManager.update(dt);

	handleMovement(dt);

	checkTransitions();
}

void WalkingState::render() {
	DrawText("Walk", 0, 20, 24, WHITE);
}

StateName WalkingState::name() {
	return m_name;
}

void WalkingState::checkTransitions() {
	constexpr uint8_t MOVEMENT_BITMASKS = 0b00000011;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	if ((inputs.back().directionHold & MOVEMENT_BITMASKS) == 0) {
		m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
	}
}

void WalkingState::handleMovement(float dt) {
	m_player->m_position.x += 200 * dt;
}
