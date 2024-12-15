#include "../../../include/IdleState.h"

#include <list>
#include <iostream>

#include "../../../include/Player.h"
#include "../../../include/State.h"
#include "../../../include/ForwardWalkState.h"
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

	checkTransitions();
}

void IdleState::render() {
	if (m_player->m_isP1)
		DrawText("P1 Idle", 0, 20, 24, WHITE);
	else
		DrawText("P2 Idle", 0, 40, 24, WHITE);
}

StateName IdleState::name() {
	return m_name;
}

void IdleState::checkTransitions() {
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	// if ((inputs.back().directionHold & LEFT_BITMASK) > 0)
	// {
	// 	m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
	// }
	// else
	// {
	// 	m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
	// }
	if (m_player->facing == Direction::Left) {
		if ((inputs.back().directionHold & LEFT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
		}
		else if ((inputs.back().directionHold & RIGHT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
		}
	}
	else {
		if ((inputs.back().directionHold & LEFT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
		}
		else if ((inputs.back().directionHold & RIGHT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
		}
	}
}
