#include "../../../include/IdleState.h"
#include "../../../include/Player.h"
#include "../../../include/State.h"

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

}

void IdleState::render() {

}

StateName IdleState::name() {
	return m_name;
}
