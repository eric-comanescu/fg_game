#include "../../../include/Player.h"

#include <list>
#include <iostream>
#include <typeinfo>
#include <algorithm>
#include <sstream>
#include <cassert>

#include "../../../include/raylib.h"
#include "../../../include/IdleState.h"
#include "../../../include/ForwardWalkState.h"
#include "../../../include/BackwardsWalkState.h"
#include "../../../include/CrouchState.h"
#include "../../../include/CrouchBlockState.h"
#include "../../../include/AttackState.h"
#include "../../../include/BlockstunState.h"
#include "../../../include/HitstunState.h"
#include "../../../include/Attack.h"
#include "../../../include/Input.h"
#include "../../../include/Hitbox.h"
#include "../../../include/GameEntity.h"
#include "../../../include/Animation.h"

Player::Player(Vector2 pos, Vector2 dimensions, bool isP1, Hitbox hitboxOffsets)
	: m_isP1{isP1} {
	m_stateMachine.add(new ForwardWalkState(this));
	m_stateMachine.add(new BackwardsWalkState(this));
	m_stateMachine.add(new CrouchState(this));
	m_stateMachine.add(new CrouchBlockState(this));
	m_stateMachine.add(new AttackState(this));
	m_stateMachine.add(new IdleState(this));
	m_stateMachine.add(new BlockstunState(this));
	m_stateMachine.add(new HitstunState(this));
	m_stateMachine.add(new DeathState(this));

	m_stateMachine.change(StateName::Player_Idle_State, nullptr);

	m_attacks.push_back(new Attack(
		this, 
		new Animation({
			(Rectangle){0.0f, 300.0f, 100.0f, 100.0f},
			(Rectangle){100.0f, 300.0f, 100.0f, 100.0f},
			(Rectangle){200.0f, 300.0f, 100.0f, 100.0f},
			(Rectangle){300.0f, 300.0f, 100.0f, 100.0f},
			(Rectangle){400.0f, 300.0f, 100.0f, 100.0f},
			(Rectangle){500.0f, 300.0f, 100.0f, 100.0f}
		}, 5, 0),
		{0b00001000}, 
		Hitbox(30, 20, 20, 15, RED),
		Attack::AttackStrength::Low, 
		false, 
		7,
		0)
	);
	m_attacks.push_back(new Attack(
		this, 
		new Animation({
			(Rectangle){100.0f, 400.0f, 100.0f, 100.0f},
			(Rectangle){200.0f, 400.0f, 100.0f, 100.0f},
			(Rectangle){300.0f, 400.0f, 100.0f, 100.0f},
			(Rectangle){400.0f, 400.0f, 100.0f, 100.0f},
			(Rectangle){500.0f, 400.0f, 100.0f, 100.0f},
			(Rectangle){0.0f, 400.0f, 100.0f, 100.0f},
		}, 5, 0),
		{0b00001000}, 
		Hitbox(30, 30, 32, 16, RED),
		Attack::AttackStrength::Low, 
		true, 
		10,
		0)
	);

	m_sprites = LoadTexture("../src/assets/fer_sprites.png");

	assert(IsTextureReady(m_sprites) && "Player spritesheet Texture failed to load");

	std::sort(m_attacks.begin(), m_attacks.end(), [](Attack* a, Attack* b) {
		return a->m_priority < b->m_priority;
	});

	m_position = pos;
	m_prevPosition = pos;
	m_dimensions = dimensions;

	if (m_isP1)
		m_inputManager.m_keybinds = {
			{InputManager::Action::Up_Input, KEY_W},
			{InputManager::Action::Down_Input, KEY_S},
			{InputManager::Action::Left_Input, KEY_A},
			{InputManager::Action::Right_Input, KEY_D},
			{InputManager::Action::Light_Input, KEY_Y},
			{InputManager::Action::Medium_Input, KEY_U},
			{InputManager::Action::Heavy_Input, KEY_I},
		};
	else
		m_inputManager.m_keybinds = {
			{InputManager::Action::Up_Input, KEY_UP},
			{InputManager::Action::Down_Input, KEY_DOWN},
			{InputManager::Action::Left_Input, KEY_LEFT},
			{InputManager::Action::Right_Input, KEY_RIGHT},
			{InputManager::Action::Light_Input, KEY_LEFT_BRACKET},
			{InputManager::Action::Medium_Input, KEY_RIGHT_BRACKET},
			{InputManager::Action::Heavy_Input, KEY_BACKSLASH},
		};
	
	m_hurtboxOffsets = hitboxOffsets;
	m_hurtbox.set(
		m_position.x + hitboxOffsets.position().x,
		m_position.y + hitboxOffsets.position().y,
		m_dimensions.x + hitboxOffsets.dimensions().x,
		m_dimensions.y + hitboxOffsets.dimensions().y
	);
	m_hurtbox.isActive = true;
}

Player::~Player() {
	for (auto& attack : m_attacks) {
		delete attack;
	}

	UnloadTexture(m_sprites);
}

void Player::update(float dt) {
	m_hurtbox.set(
		m_position.x + m_hurtboxOffsets.position().x,
		m_position.y + m_hurtboxOffsets.position().y,
		m_hurtboxOffsets.dimensions().x,
		m_hurtboxOffsets.dimensions().y
	);

	m_stateMachine.update(dt);
}

void Player::render() {
	m_stateMachine.render();
}

bool Player::didCollideWith(const Hitbox& target) {
	return m_hurtbox.didCollide(target);
}

const Hitbox& Player::hitbox() {
	return m_hurtbox;
}

void Player::onCollision(GameEntity* collider) {
	if (collider == this) {
		return;
	}

	// set collider position outside of collidee
	m_position.x = m_prevPosition.x;
}

void Player::onHit(Player* attacker, Attack* attack) {
	if (!attack->m_hitbox.isConsumed) {
		attack->m_hitbox.isConsumed = true;
	}
	else {
		return;
	}

	if (!m_isBlocking) {
		hp -= attack->m_damage;

		// Apply pushback on hit
		constexpr float PUSHBLOCK_DISTANCE = 2.0f;
		if (attacker->facing == Direction::Right) {
			if (attacker->m_position.x - PUSHBLOCK_DISTANCE < 0) {
				float overflow = attacker->m_position.x - PUSHBLOCK_DISTANCE;

				attacker->m_pushBlockDistance += PUSHBLOCK_DISTANCE + overflow;
				m_pushBlockDistance += -overflow;
			}
			else {
				attacker->m_pushBlockDistance += PUSHBLOCK_DISTANCE;
			}
		}
		else {
			if (attacker->m_position.x + attacker->m_dimensions.x + PUSHBLOCK_DISTANCE > 320) {
				float overflow = -(attacker->m_position.x + attacker->m_dimensions.x + PUSHBLOCK_DISTANCE - 320);

				attacker->m_pushBlockDistance += PUSHBLOCK_DISTANCE + overflow;
				m_pushBlockDistance += -overflow;
			}
			else {
				attacker->m_pushBlockDistance += PUSHBLOCK_DISTANCE;
			}
		}

		// TODO: add flinch state
		m_stateMachine.change(StateName::Player_HitStun_State, &attack->m_attackStrength);
	}
	else {
		// TODO: Remove chip on normals
		hp -= attack->m_damage / 5.0f;

		// Apply pushback on block
		constexpr float PUSHBLOCK_DISTANCE = 5.0f;
		if (attacker->facing == Direction::Right) {
			if (attacker->m_position.x - PUSHBLOCK_DISTANCE < 0) {
				float overflow = attacker->m_position.x - PUSHBLOCK_DISTANCE;

				attacker->m_pushBlockDistance = PUSHBLOCK_DISTANCE + overflow;
				m_pushBlockDistance = -overflow;
			}
			else {
				attacker->m_pushBlockDistance = PUSHBLOCK_DISTANCE;
			}
		}
		else {
			if (attacker->m_position.x + attacker->m_dimensions.x + PUSHBLOCK_DISTANCE > 320) {
				float overflow = -(attacker->m_position.x + attacker->m_dimensions.x + PUSHBLOCK_DISTANCE - 320);

				attacker->m_pushBlockDistance = PUSHBLOCK_DISTANCE + overflow;
				m_pushBlockDistance = -overflow;
			}
			else {
				attacker->m_pushBlockDistance = PUSHBLOCK_DISTANCE;
			}
		}

		m_stateMachine.change(StateName::Player_BlockStun_State, &attack->m_attackStrength);
	}
}

void Player::change(StateName stateName, void* params) {
	m_stateMachine.change(stateName, params);
}
