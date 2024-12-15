#include "../include/Fight.h"

#include <iostream>

#include "../include/Player.h"
#include "../include/raylib.h"
#include "../include/Direction.h"

Fight::Fight(Vector2 player1Pos, Vector2 player2Pos)
	: m_player1(player1Pos)
	, m_player2(player2Pos) {

}

Fight::~Fight() {

}

void Fight::update(float dt) {
	m_player1.update(dt);

	// TODO: uncomment when done testing
	m_player2.update(dt);
}

void Fight::render() {
	m_player1.render();

	// TODO: uncomment when done testing
	m_player2.render();
}
