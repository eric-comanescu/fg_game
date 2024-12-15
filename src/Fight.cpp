#include "../include/Fight.h"

#include <iostream>

#include "../include/Player.h"
#include "../include/raylib.h"
#include "../include/Direction.h"

Fight::Fight(Vector2 player1Pos, Vector2 p1Dims, Vector2 player2Pos, Vector2 p2Dims)
	: m_player1(new Player(player1Pos, p1Dims, true, Hitbox()))
	, m_player2(new Player(player2Pos, p2Dims, false, Hitbox())) {
	m_entities.push_back(m_player1);
	m_entities.push_back(m_player2);
}

Fight::~Fight() {

}

void Fight::update(float dt) {
	setPlayerDirections();

	updateEntities(dt);

	m_player1->m_prevPosition = m_player1->m_position;
	m_player2->m_prevPosition = m_player2->m_position;
}

void Fight::render() {
	for (const auto& entity : m_entities) {
		entity->render();
	}
}

void Fight::setPlayerDirections() {
	if (m_player1->m_position.x < m_player2->m_position.x) {
		m_player1->facing = Direction::Right;
		m_player2->facing = Direction::Left;
	}
	else {
		m_player1->facing = Direction::Left;
		m_player2->facing = Direction::Right;
	}
}

void Fight::updateEntities(float dt) {
	for (auto entity : m_entities) {
		if (entity->hp <= 0) {
			// handle dead entity logic
		}

		entity->update(dt);

		for (auto entity2 : m_entities) {
			if (entity->didCollideWith(entity2->hitbox())) {
				entity->onCollision(entity2);
			}
		}
	}
}
