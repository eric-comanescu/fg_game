#include "../../../include/PlayState.h"
#include "../../../include/State.h"

#include <iostream>

#include "../../../include/Fight.h"
#include "../../../include/raylib.h"

PlayState::PlayState() 
	: State() {

};

PlayState::~PlayState() {

}

void PlayState::enter(void* params) {
	Player* p1 = new Player(Player::PLAYER1_STARTING_POS, Player::STANDING_DIMENSIONS, true, Hitbox());
	Player* p2 = new Player(Player::PLAYER2_STARTING_POS, Player::STANDING_DIMENSIONS, false, Hitbox());
	
	m_fight = new Fight(p1, p2, &m_timer);
	m_ui = new UserInterface(p1, p2, &m_timer);
}

void PlayState::exit() {

}

void PlayState::update(float dt) {
	m_ui->update(dt);
	m_fight->update(dt);
}

void PlayState::render() {
	m_ui->render();
	m_fight->render();
}

StateName PlayState::name() {
	return m_name;
}
