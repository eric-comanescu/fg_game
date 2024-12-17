#include "../../include/UserInterface.h"

#include <iostream>

#include "../../include/Player.h"

UserInterface::UserInterface(Player* p1, Player* p2)
	: m_player1 {p1}
	, m_player2 {p2} {

}

UserInterface::~UserInterface() {

}

void UserInterface::update(float dt) {
	m_p1TargetWidth = m_player1->hp / m_player1->maxHp * UserInterface::HP_BAR_WIDTH;
	m_p2TargetWidth = m_player2->hp / m_player2->maxHp * UserInterface::HP_BAR_WIDTH;
}

void UserInterface::render() {
	if (m_p1HpWidth > m_p1TargetWidth) {
		m_p1HpWidth -= 0.5f;
	}
	DrawRectangle(10, 10, m_p1HpWidth, 10, GREEN);

	if (m_p2HpWidth > m_p2TargetWidth) {
		m_p2HpWidth -= 0.5f;
	}
	DrawRectangle(190, 10, m_p2HpWidth, 10, GREEN);

	DrawRectangleLines(10, 10, UserInterface::HP_BAR_WIDTH, 10, GRAY);
	DrawRectangleLines(320 - 130, 10, UserInterface::HP_BAR_WIDTH, 10, GRAY);
}
