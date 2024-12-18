#include "../include/Fight.h"

#include <iostream>

#include "../include/Player.h"
#include "../include/raylib.h"
#include "../include/Direction.h"
#include "../include/StateStack.h"
#include "../include/UserInterface.h"
#include "../include/RoundIntroState.h"

Fight::Fight(Player* p1, Player* p2, float* timer, StateStack* sm, UserInterface* ui)
	: m_player1(p1)
	, m_player2(p2)
	, m_timer {timer}
	, m_sm {sm}
	, m_ui {ui} {
	m_entities.push_back(m_player1);
	m_entities.push_back(m_player2);
}

Fight::~Fight() {

}

void Fight::update(float dt) {
	setPlayerDirections();

	*m_timer -= dt;

	if (*m_timer <= 0) {
		handleRoundEnd();
	}

	updateEntities(dt);

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
	handleRoundEnd();

	for (auto entity : m_entities) {
		entity->update(dt);

		for (auto entity2 : m_entities) {
			if (entity->didCollideWith(entity2->hitbox())) {
				entity->onCollision(entity2);
			}
			else {
				m_player1->m_prevPosition = m_player1->m_position;
				m_player2->m_prevPosition = m_player2->m_position;
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

void Fight::handleRoundEnd() {
	if (*m_timer > 0) {
		if (m_player1->hp <= 0 && m_player2->hp <= 0) {
			// TODO: DRAW

			m_sm->push(new RoundIntroState(m_sm), new RoundIntroState::RoundIntroEnterParams {
				this,
				m_ui,
				m_player1,
				m_player2,
				0
			});
		}
		else if (m_player1->hp <= 0) {
			// TODO: P1 LOSS
			m_player2->roundsWon++;

			m_sm->push(new RoundIntroState(m_sm), new RoundIntroState::RoundIntroEnterParams {
				this,
				m_ui,
				m_player1,
				m_player2,
				2
			});
		}
		else if (m_player2->hp <= 0) {
			// TODO: P2 LOSS
			m_player1->roundsWon++;

			m_sm->push(new RoundIntroState(m_sm), new RoundIntroState::RoundIntroEnterParams {
				this,
				m_ui,
				m_player1,
				m_player2,
				1
			});
		}
	}
	else {
		if (m_player1->hp == m_player2->hp) {
			// TODO: Draw

			m_sm->push(new RoundIntroState(m_sm), new RoundIntroState::RoundIntroEnterParams {
				this,
				m_ui,
				m_player1,
				m_player2,
				0
			});
		}
		else if (m_player1->hp > m_player2->hp) {
			// TODO: P1 win
			m_player1->roundsWon++;

			m_sm->push(new RoundIntroState(m_sm), new RoundIntroState::RoundIntroEnterParams {
				this,
				m_ui,
				m_player1,
				m_player2,
				1
			});
		}
		else {
			// TODO: P2 win
			m_player2->roundsWon++;

			m_sm->push(new RoundIntroState(m_sm), new RoundIntroState::RoundIntroEnterParams {
				this,
				m_ui,
				m_player1,
				m_player2,
				2
			});
		}
	}
}

void Fight::reset() {
	m_player1->m_position = Player::PLAYER1_STARTING_POS;
	m_player2->m_position = Player::PLAYER2_STARTING_POS;

	m_player1->m_hurtboxOffsets.dimensions() = Player::STANDING_DIMENSIONS;
	m_player2->m_hurtboxOffsets.dimensions() = Player::STANDING_DIMENSIONS;

	m_player1->hp = m_player1->maxHp;
	m_player2->hp = m_player2->maxHp;

	*m_timer = 99.9f;
}
