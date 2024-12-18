#include "../../../include/RoundIntroState.h"
#include "../../../include/State.h"

#include <iostream>
#include <cassert>
#include <tuple>

#include "../../../include/UserInterface.h"
#include "../../../include/Player.h"
#include "../../../include/raylib.h"
#include "../../../include/StateStack.h"

RoundIntroState::RoundIntroState(StateStack* sm)
	: State()
	, m_sm {sm} {

}

RoundIntroState::~RoundIntroState() {

}

void RoundIntroState::enter(void* params) {
	assert(params != nullptr && "Dont pass in null to RoundIntroState that");

	RoundIntroEnterParams* enterParams = reinterpret_cast<RoundIntroEnterParams*>(params);

	m_ui = enterParams->ui;

	m_p1 = enterParams->p1;
	m_p2 = enterParams->p2;

	if (m_winner == 1) {
		m_p1->change(StateName::Player_Idle_State, nullptr);

		// TODO: Change lose to die state
		m_p2->change(StateName::Player_Idle_State, nullptr);
	}
	else if (m_winner == 2) {
		m_p2->change(StateName::Player_Idle_State, nullptr);

		// TODO: Change lose to die state
		m_p1->change(StateName::Player_Idle_State, nullptr);
	}
	else {
		// TODO: Tie
	}

	delete enterParams;
}

void RoundIntroState::exit() {

}

void RoundIntroState::update(float dt) {
	m_ui->update(dt);

	if (m_timer -= dt; m_timer <= 0) {
		m_sm->pop();
	}
}

void RoundIntroState::render() {
	m_ui->render();
	m_p1->render();
	m_p2->render();

	DrawText("Round Intro State",0,0,24, WHITE);
}

StateName RoundIntroState::name() {
	return m_name;
}
