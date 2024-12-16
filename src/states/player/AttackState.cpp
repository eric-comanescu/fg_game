#include "../../../include/AttackState.h"

#include <sstream>

#include "../../../include/Player.h"
#include "../../../include/Attack.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"
#include "../../../include/raylib.h"

AttackState::AttackState(Player* player)
	: State()
	, m_player {player} {

}

AttackState::~AttackState() {

}

void AttackState::enter(void* params) {
	m_attack = reinterpret_cast<Attack*>(params);
	m_duration = m_attack->m_duration;
}

void AttackState::exit() {

}

void AttackState::update(float dt) {
	m_player->m_inputManager.update(dt);

	m_duration -= dt;

	checkTranstions();
}

void AttackState::render() {
	std::stringstream ss;

	if (m_player->m_isP1)
		ss << "P1 Attack: " << m_duration;
	else
		ss << "P2 Attack: " << m_duration;

	if (m_player->m_isP1)
		DrawText(ss.str().c_str(), 0, 20, 24, WHITE);
	else
		DrawText(ss.str().c_str(), 0, 40, 24, WHITE);
}

StateName AttackState::name() {
	return m_name;
}

void AttackState::checkTranstions() {
	if (m_duration > 0)
		return;
	
	// do stuff
	m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
}
