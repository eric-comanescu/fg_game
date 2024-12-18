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

	m_fight = enterParams->fight;
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
	m_startTween = false;
	m_undoTween = false;
	m_tweenTimer = 1.0f;
	m_reverseTimer = 0.0f;
	m_timer = 3.0f;
}

void RoundIntroState::update(float dt) {
	m_ui->update(dt);

	if (m_timer -= dt; m_timer <= 0) {
		m_startTween = true;
	}

	if (m_startTween) {
		m_tweenTimer -= dt;
	}

	if (m_tweenTimer <= 0) {
		m_undoTween = true;
		m_startTween = false;
	}

	if (m_undoTween) {
		m_fight->reset();
		m_fight->update(dt);
		m_ui->reset();

		if (m_fadeDelay -= dt; m_fadeDelay <= 0) {
			m_reverseTimer += dt;
		}

		if (m_reverseTimer > 1) {
			m_reverseTimer = 1;
			m_shouldPop = true;
		};
	}

	if (m_shouldPop) {
		m_sm->pop();
	}
}

void RoundIntroState::render() {
	m_ui->render();
	m_p1->render();
	m_p2->render();

	if (m_startTween) {
		DrawRectangle(0, 0, 320, 180, (Color){0, 0, 0, static_cast<unsigned char>((1 - m_tweenTimer / 1.0f) * 255)});
	}
	else if (m_undoTween) {
		DrawRectangle(0, 0, 320, 180, (Color){0, 0, 0, static_cast<unsigned char>(m_tweenTimer / 1.0f * 255)});
	}
}

StateName RoundIntroState::name() {
	return m_name;
}
