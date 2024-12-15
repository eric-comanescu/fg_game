#include "../include/Fight.h"

#include <iostream>

#include "../include/Player.h"
#include "../include/raylib.h"
#include "../include/Direction.h"

Fight::Fight(Vector2 player1Pos, Vector2 player2Pos)
	: m_player1(player1Pos, true)
	, m_player2(player2Pos, false) {

}

Fight::~Fight() {

}

void Fight::update(float dt) {
	setPlayerDirections();

	m_player1.update(dt);

	// TODO: uncomment when done testing
	m_player2.update(dt);
}

void Fight::render() {
	m_player1.render();

	// TODO: uncomment when done testing
	m_player2.render();
}

void Fight::setPlayerDirections() {
	if (m_player1.m_position.x < m_player2.m_position.x) {
		m_player1.facing = Direction::Right;
		m_player2.facing = Direction::Left;
	}
	else {
		m_player1.facing = Direction::Left;
		m_player2.facing = Direction::Right;
	}
}
