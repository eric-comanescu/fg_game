#include "../include/Fight.h"

#include <iostream>

#include "../include/Player.h"
#include "../include/raylib.h"
#include "../include/Direction.h"

Fight::Fight(Player* p1, Player* p2)
	: m_player1(p1)
	, m_player2(p2) {
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
	if (m_player1->hp <= 0 && m_player2->hp <= 0) {
		// TODO: DRAW
	}
	else if (m_player1->hp <= 0) {
		// TODO: P1 LOSS
		m_player2->roundsWon++;
	}
	else if (m_player2->hp <= 0) {
		// TODO: P2 LOSS
		m_player1->roundsWon++;
	}
	for (auto entity : m_entities) {
		entity->update(dt);

		for (auto entity2 : m_entities) {
			if (entity->didCollideWith(entity2->hitbox())) {
				entity->onCollision(entity2);
			}
		}

		if (m_player1->m_activeHitbox != nullptr && m_player1->m_activeHitbox->isActive) {
			if (m_player2->didCollideWith(*m_player1->m_activeHitbox)) {
				m_player2->onHit(m_player1, m_player1->m_activeAttack);
			}
		}

		if (m_player2->m_activeHitbox != nullptr && m_player2->m_activeHitbox->isActive) {
			if (m_player1->didCollideWith(*m_player2->m_activeHitbox)) {
				m_player1->onHit(m_player2, m_player2->m_activeAttack);
			}
		}
	}
}
