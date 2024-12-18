#include "../../include/UserInterface.h"

#include <iostream>
#include <sstream>

#include "../../include/Player.h"
#include "../../include/Game.h"
#include "../../include/raylib.h"

UserInterface::UserInterface(Player* p1, Player* p2, float* timer)
	: m_player1 {p1}
	, m_player2 {p2}
	, m_timer {timer} {

}

UserInterface::~UserInterface() {

}

void UserInterface::update(float dt) {
	m_p1TargetWidth = m_player1->hp / m_player1->maxHp * UserInterface::HP_BAR_WIDTH;
	m_p2TargetWidth = m_player2->hp / m_player2->maxHp * UserInterface::HP_BAR_WIDTH;
}

void UserInterface::render() {
	// P1 HP BAR
	if (m_p1HpWidth > m_p1TargetWidth) {
		m_p1HpWidth -= 0.5f;
	}
	DrawRectangle(10, 10, m_p1HpWidth, 10, GREEN);

	// P2 HP BAR
	if (m_p2HpWidth > m_p2TargetWidth) {
		m_p2HpWidth -= 0.5f;
	}
	DrawRectangle(190, 10, m_p2HpWidth, 10, GREEN);

	// HP BAR OUTLINE
	DrawRectangleLines(10, 10, UserInterface::HP_BAR_WIDTH, 10, GRAY);
	DrawRectangleLines(320 - 130, 10, UserInterface::HP_BAR_WIDTH, 10, GRAY);

	// P1 Rounds won indicator
	if (m_player1->roundsWon > 0) {
		DrawCircle(20, 30, 5, RED);
	}
	if (m_player1->roundsWon > 1) {
		DrawCircle(35, 30, 5, RED);
	}

	DrawCircleLines(20, 30, 5, GRAY);
	DrawCircleLines(35, 30, 5, GRAY);

	// P2 Rounds won indicator
	if (m_player2->roundsWon > 0) {
		DrawCircle(300, 30, 5, RED);
	}
	if (m_player2->roundsWon > 1) {
		DrawCircle(285, 30, 5, RED);
	}

	DrawCircleLines(300, 30, 5, GRAY);
	DrawCircleLines(285, 30, 5, GRAY);

	// Timer
	std::stringstream ss;
	ss << static_cast<int>(*m_timer);

	DrawTextEx(Game::Font, ss.str().c_str(), (Vector2){148, 10}, 24, 1, WHITE);
}
