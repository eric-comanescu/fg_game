#include "../../../include/IdleState.h"

#include <list>
#include <iostream>

#include "../../../include/Player.h"
#include "../../../include/State.h"
#include "../../../include/ForwardWalkState.h"
#include "../../../include/Input.h"

IdleState::IdleState(Player* player)
	: State{}
	, m_player { player }
{
	m_animation = new Animation({
		(Rectangle){0.0f,0.0f,100.0f,100.0f},
		(Rectangle){100.0f,0.0f,100.0f,100.0f},
		(Rectangle){200.0f,0.0f,100.0f,100.0f},
		(Rectangle){300.0f,0.0f,100.0f,100.0f}
	}, 25);
};

IdleState::~IdleState() {

}

void IdleState::enter(void* params = nullptr) {
	m_player->m_hurtboxOffsets.position() = Player::IDLE_HURTBOX_OFFSETS;
	m_player->m_hurtboxOffsets.dimensions() = Player::IDLE_HURTBOX_DIMENSIONS;

	m_player->m_isCrouching = false;
}

void IdleState::exit() {

}

void IdleState::update(float dt) {
	m_player->m_inputManager.update(dt);

	m_animation->update(dt);

	checkTransitions();
}

void IdleState::render() {
	if (m_player->facing == Direction::Right) {
		DrawTexturePro(
			m_player->m_sprites,
			m_animation->currentSprite(),
			(Rectangle){m_player->m_position.x, m_player->m_position.y, m_player->m_dimensions.x, m_player->m_dimensions.y},
			{0.0f, 0.0f},
			0.0f,
			WHITE);
	}
	else {
		DrawTexturePro(
			m_player->m_sprites,
			m_animation->currentSpriteFlipped(),
			(Rectangle){m_player->m_position.x, m_player->m_position.y, m_player->m_dimensions.x, m_player->m_dimensions.y},
			{0.0f, 0.0f},
			0.0f,
			WHITE);
	}
}

StateName IdleState::name() {
	return m_name;
}

void IdleState::checkTransitions() {
	constexpr uint8_t DOWN_BITMASK = 0b00000100;
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	// TODO: Change to more complex attack detection when implementing multiple attacks
	if ((inputs.back().attackPress & LATTACK_BITMASK) != 0) {
		if ((inputs.back().directionHold & DOWN_BITMASK) == 0) {
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
		}
		else {
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[1]);
		}
	}

	if (m_player->facing == Direction::Left) {
		if ((inputs.back().directionHold & LEFT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
		}
		else if ((inputs.back().directionHold & RIGHT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
		}
		else if ((inputs.back().directionHold & DOWN_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
	else {
		if ((inputs.back().directionHold & LEFT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
		}
		else if ((inputs.back().directionHold & RIGHT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
		}
		else if ((inputs.back().directionHold & DOWN_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
}
