#include "../../../include/IdleState.h"

#include <list>
#include <stdlib.h>

#include "../../../include/Player.h"
#include "../../../include/State.h"
#include "../../../include/WalkingState.h"
#include "../../../include/Input.h"

IdleState::IdleState(Player* player)
	: State{}
	, m_player { player }
{};

IdleState::~IdleState() {

}

void IdleState::enter(void* params = nullptr) {

}

void IdleState::exit() {

}

void IdleState::update(float dt) {
	m_player->m_inputManager.update(dt);
}

void IdleState::render() {

}

StateName IdleState::name() {
	return m_name;
}

void IdleState::checkTransitions() {
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	if ((inputs.back().directionHold & LEFT_BITMASK) > 0) {
		m_player->m_stateMachine.change(StateName::Walking_State, nullptr);
	}

	if ((inputs.back().directionHold & RIGHT_BITMASK) > 0) {
		m_player->m_stateMachine.change(StateName::Walking_State, nullptr);
	}
}
