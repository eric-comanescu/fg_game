#include "../../../include/AttackState.h"

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
}

void AttackState::exit() {

}

void AttackState::update(float dt) {
	m_player->m_inputManager.update(dt);

	checkTranstions();
}

void AttackState::render() {
	if (m_player->m_isP1)
		DrawText("P1 Attack", 0, 20, 24, WHITE);
	else
		DrawText("P2 Attack", 0, 40, 24, WHITE);
}

StateName AttackState::name() {
	return m_name;
}

void AttackState::checkTranstions() {

}
