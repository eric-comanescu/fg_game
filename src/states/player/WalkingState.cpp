#include "../../../include/WalkingState.h"

#include <iostream>

#include "../../../include/Player.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"

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
	checkTransitions();

	m_player->m_stateMachine.update(dt);
	handleMovement(dt);
}

void WalkingState::render() {

}

StateName WalkingState::name() {
	return m_name;
}

void WalkingState::checkTransitions() {
	printf("crash in check transitions\n");

	constexpr uint8_t MOVEMENT_BITMASKS = 0b00000011;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	if ((inputs.back().directionHold & MOVEMENT_BITMASKS) != 0) {
		m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
	}
}

void WalkingState::handleMovement(float dt) {
	printf("crash in handle movement");

	if (m_walkingDirection == Direction::Left) {
		m_player->m_position.x += 200 * dt;
	}

	if (m_walkingDirection == Direction::Right) {
		m_player->m_position.x -= 200 * dt;
	}
}
