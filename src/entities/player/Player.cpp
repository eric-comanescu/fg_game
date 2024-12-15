#include "../../../include/Player.h"

#include <list>
#include <iostream>

#include "../../../include/raylib.h"
#include "../../../include/IdleState.h"
#include "../../../include/WalkingState.h"
#include "../../../include/Input.h"

Player::Player(Vector2 pos) {
	m_stateMachine.add(new WalkingState(this));
	m_stateMachine.add(new IdleState(this));

	m_position = pos;
}

Player::~Player() {

}

void Player::update(float dt) {
	m_stateMachine.update(dt);
}

void Player::render() {
	// Temporary, for testing
	// m_inputManager.debugRender();

	m_stateMachine.render();

	DrawRectangle(m_position.x, m_position.y, 50, 90, BLUE);
}
