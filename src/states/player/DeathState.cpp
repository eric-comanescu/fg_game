#include "../../../include/IdleState.h"

#include <list>
#include <iostream>

#include "../../../include/Player.h"
#include "../../../include/State.h"
#include "../../../include/Input.h"
#include "../../../include/raylib.h"

DeathState::DeathState(Player* player)
	: State()
	, m_player {player} {
	m_animation = new Animation({
		(Rectangle){0.0f, 600.0f,100.0f,100.0f},
		(Rectangle){100.0f, 600.0f,100.0f,100.0f},
		(Rectangle){200.0f, 600.0f,100.0f,100.0f},
		(Rectangle){300.0f, 600.0f,100.0f,100.0f},
		(Rectangle){400.0f, 600.0f,100.0f,100.0f},
		(Rectangle){500.0f, 600.0f,100.0f,100.0f},
		(Rectangle){600.0f, 600.0f,100.0f,100.0f},
	}, 10, 1);
}

DeathState::~DeathState() {

}

void DeathState::enter(void* params) {

}

void DeathState::exit() {
	m_animation->reset();
}

void DeathState::update(float dt) {
	m_animation->update(dt);
}

void DeathState::render() {
	if (!m_animation->isDone()) {
		if (m_player->facing == Direction::Right)
		{
			DrawTexturePro(
				m_player->m_sprites,
				m_animation->currentSprite(),
				(Rectangle){m_player->m_position.x, m_player->m_position.y, m_player->m_dimensions.x, m_player->m_dimensions.y},
				{0.0f, 0.0f},
				0.0f,
				WHITE);
		}
		else
		{
			DrawTexturePro(
				m_player->m_sprites,
				m_animation->currentSpriteFlipped(),
				(Rectangle){m_player->m_position.x, m_player->m_position.y, m_player->m_dimensions.x, m_player->m_dimensions.y},
				{0.0f, 0.0f},
				0.0f,
				WHITE);
		}
	}
}

StateName DeathState::name() {
	return m_name;
}

void DeathState::checkTransitions() {

}
