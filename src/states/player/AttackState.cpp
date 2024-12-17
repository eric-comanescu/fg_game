#include "../../../include/AttackState.h"

#include <sstream>

#include "../../../include/Player.h"
#include "../../../include/Attack.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"
#include "../../../include/Direction.h"
#include "../../../include/raylib.h"

AttackState::AttackState(Player* player)
	: State()
	, m_player {player} {

}

AttackState::~AttackState() {

}

void AttackState::enter(void* params) {
	m_attack = reinterpret_cast<Attack*>(params);
	m_duration = m_attack->m_duration;

	if (m_attack->m_isLow) {
		m_player->m_dimensions = Player::CROUCHING_DIMENSIONS;
		m_player->m_position.y += 40;
	}
}

void AttackState::exit() {
	m_player->m_dimensions = Player::STANDING_DIMENSIONS;

	if (m_attack->m_isLow)
		m_player->m_position.y -= 40;
}

void AttackState::update(float dt) {
	m_player->m_inputManager.update(dt);
	m_attack->m_hitbox.set(
		m_player->m_position.x + m_attack->m_hitboxOffset.position().x,
		m_player->m_position.y + m_attack->m_hitboxOffset.position().y,
		m_attack->m_hitboxOffset.dimensions().x,
		m_attack->m_hitboxOffset.dimensions().y
	);

	if (m_attack->m_animation->currentFrame() == 1)
		m_attack->m_hitbox.isActive = true;
	else
		m_attack->m_hitbox.isActive = false;

	m_attack->m_animation->update(dt);

	m_duration -= dt;

	checkTranstions();
}

void AttackState::render() {
	std::stringstream ss;

	if (m_player->m_isP1)
		ss << "P1 Attack Frame: " << m_attack->m_animation->currentFrame();
	else
		ss << "P2 Attack Frame: " << m_attack->m_animation->currentFrame();

	if (m_player->m_isP1)
		DrawText(ss.str().c_str(), 0, 20, 24, WHITE);
	else
		DrawText(ss.str().c_str(), 0, 40, 24, WHITE);

	m_attack->m_hitbox.render();
}

StateName AttackState::name() {
	return m_name;
}

void AttackState::checkTranstions() {
	// TODO: Check if consumed to allow cancels
	if (m_duration > 0)
		return;
	
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;
	constexpr uint8_t DOWN_BITMASK = 0b00000100;

	constexpr uint8_t LATTACK_BITMASK = 0b00001000;

	const InputManager::Input& input { m_player->m_inputManager.getInputList().back() };

	// TODO: More complex (check idle state)
	if ((input.attackPress & LATTACK_BITMASK) != 0) {
		if ((input.directionHold & DOWN_BITMASK) != 0)
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[1]);
		else
			m_player->m_stateMachine.change(StateName::Player_Attack_State, m_player->m_attacks[0]);
	}

	if (m_player->facing == Direction::Right) {
		if ((input.directionHold & DOWN_BITMASK) == 0) {
			if ((input.directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if((input.directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add else if for jump (UP_BITMASK)
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((input.directionHold & LEFT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouch_Blocking_State, nullptr);
		}
		else {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
	else {
		if ((input.directionHold & DOWN_BITMASK) == 0) {
			if ((input.directionHold & LEFT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Forward_Walking_State, nullptr);
			}
			else if((input.directionHold & RIGHT_BITMASK) != 0) {
				m_player->m_stateMachine.change(StateName::Player_Backwards_Walking_State, nullptr);
			}
			// TODO: Add else if for jump (UP_BITMASK)
			else {
				m_player->m_stateMachine.change(StateName::Player_Idle_State, nullptr);
			}
		}
		else if ((input.directionHold & RIGHT_BITMASK) != 0) {
			m_player->m_stateMachine.change(StateName::Player_Crouch_Blocking_State, nullptr);
		}
		else {
			m_player->m_stateMachine.change(StateName::Player_Crouching_State, nullptr);
		}
	}
}
