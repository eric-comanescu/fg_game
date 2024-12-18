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
	m_imBg = LoadImageAnim("../src/assets/bg.gif", &m_bgFrames);
	m_texBg = LoadTextureFromImage(m_imBg);
}

UserInterface::~UserInterface() {
	UnloadTexture(m_texBg);
	UnloadImage(m_imBg);
}

void UserInterface::update(float dt) {
	updateBg(dt);

	m_p1TargetWidth = m_player1->hp / m_player1->maxHp * UserInterface::HP_BAR_WIDTH;
	m_p2TargetWidth = m_player2->hp / m_player2->maxHp * UserInterface::HP_BAR_WIDTH;
}

void UserInterface::render() {
	// render bg
	DrawTexture(m_texBg, 0, 0, WHITE);

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

	DrawTextEx(Game::Font, ss.str().c_str(), (Vector2){148, 3}, 24, 1, WHITE);
}

void UserInterface::updateBg(float dt) {
	if (m_currentInterval += dt; m_currentInterval >= m_bgInterval) {
		m_currentInterval = 0.0f;

		m_currentBgFrame++;
		if (m_currentBgFrame >= m_bgFrames) m_currentBgFrame = 0;

		m_nextFrameDataOffset = m_imBg.width*m_imBg.height*4*m_currentBgFrame;

		UpdateTexture(m_texBg, ((unsigned char *)m_imBg.data) + m_nextFrameDataOffset);
	}
}

void UserInterface::reset() {
	m_p1HpWidth = UserInterface::HP_BAR_WIDTH;
	m_p1TargetWidth = UserInterface::HP_BAR_WIDTH;
	m_p2HpWidth = UserInterface::HP_BAR_WIDTH;
	m_p2TargetWidth = UserInterface::HP_BAR_WIDTH;
}
