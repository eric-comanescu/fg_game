#include "../include/Fight.h"

#include <iostream>

#include "../include/Player.h"

Fight::Fight() {

}

Fight::~Fight() {

}

void Fight::update(float dt) {
	m_player1.update(dt);

	// TODO: uncomment when done testing
	// m_player2.update(dt);
}

void Fight::render() {
	m_player1.render();

	// TODO: uncomment when done testing
	// m_player2.render();
}
