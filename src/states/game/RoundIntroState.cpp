#include "../../../include/RoundIntroState.h"
#include "../../../include/State.h"

#include <iostream>
#include <cassert>
#include <tuple>

#include "../../../include/UserInterface.h"
#include "../../../include/Player.h"
#include "../../../include/raylib.h"
#include "../../../include/StateStack.h"
#include "../../../include/Game.h"

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

	if (m_p1->isDead && m_p2->isDead) {
		m_p1->change(StateName::Player_Death_State, nullptr);
		m_p2->change(StateName::Player_Death_State, nullptr);
	}
	else if (m_p2->isDead) {
		m_p2->change(StateName::Player_Death_State, nullptr);
	}
	else {
		m_p1->change(StateName::Player_Death_State, nullptr);
	}

	if (m_p1->roundsWon >= 2 || m_p2->roundsWon >= 2)
		m_fadeDelay = 2.0f;

	delete enterParams;
}

void RoundIntroState::exit() {
	m_startTween = false;
	m_undoTween = false;
	m_singleUpdate = false;
	m_drawWinnerText = false;
	m_tweenTimer = 1.0f;
	m_reverseTimer = 0.0f;
	m_timer = 3.0f;

	m_p1->isDead = false;
	m_p2->isDead = false;
}

void RoundIntroState::update(float dt) {
	m_ui->update(dt);

	if (m_p1->isDead)
		m_p1->update(dt);
	if (m_p2->isDead)
		m_p2->update(dt);

	if (m_timer -= dt; m_timer <= 0) {
		m_startTween = true;
	}

	if (m_startTween && m_tweenTimer > 0) {
		m_tweenTimer -= dt;
	}

	if (m_tweenTimer <= 0 && m_fadeDelay > 0) {
		m_drawWinnerText = true;
		m_fight->reset();
		m_fight->render();

		m_ui->reset();
		m_ui->render();

		m_p1->change(StateName::Player_Idle_State, nullptr);
		m_p2->change(StateName::Player_Idle_State, nullptr);

		if (!m_singleUpdate) {
			m_p1->update(dt);
			m_p2->update(dt);
			m_singleUpdate = true;
		}

		m_fadeDelay -= dt;
	}

	if (m_fadeDelay <= 0 && m_reverseTimer < 1) {
		m_drawWinnerText = false;
		m_undoTween = true;
		m_reverseTimer += dt;
	}

	if (m_reverseTimer >= 1) {
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

	if (m_drawWinnerText) {
		if (m_p1->roundsWon >= 2) {
			DrawTextEx(Game::Font, "Player 1 Wins", (Vector2){95.0f, 80.0f}, 24, 1, WHITE);
		}
		else if (m_p2->roundsWon >= 2) {
			DrawTextEx(Game::Font, "Player 2 Wins", (Vector2){95.0f, 80.0f}, 24, 1, WHITE);
		}
	}
}

StateName RoundIntroState::name() {
	return m_name;
}
