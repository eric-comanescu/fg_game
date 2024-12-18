#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Input.h"
#include "StateMachine.h"
#include "ForwardWalkState.h"
#include "BackwardsWalkState.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "CrouchBlockState.h"
#include "BlockstunState.h"
#include "AttackState.h"
#include "HitstunState.h"
#include "DeathState.h"
#include "Attack.h"
#include "Direction.h"
#include "Hitbox.h"
#include "raylib.h"

#include <vector>

class Fight;
class Attack;

class Player : public GameEntity {
	friend class IdleState;
	friend class ForwardWalkState;
	friend class BackwardsWalkState;
	friend class CrouchState;
	friend class CrouchBlockState;
	friend class AttackState;
	friend class Attack;
	friend class BlockstunState;
	friend class HitstunState;
	friend class DeathState;
	friend class Fight;
public:
	Direction facing {};

	// TODO: change constructor to protected to avoid instantiation
	Player(Vector2 pos, Vector2 dimensions, bool isP1, Hitbox hitboxOffsets);
	~Player();

	void update(float dt);
	void render();
	bool didCollideWith(const Hitbox& target);
	void onCollision(GameEntity* collider);
	void onHit(Player* attacker, Attack * attack);
	const Hitbox& hitbox();
	void change(StateName stateName, void* params = nullptr);

	static constexpr Vector2 CROUCHING_DIMENSIONS { (Vector2){50, 50} };
	static constexpr Vector2 STANDING_DIMENSIONS { (Vector2){50, 90} };
	static constexpr Vector2 DIMENSIONS { (Vector2){100, 100} };
	static constexpr Vector2 PLAYER1_STARTING_POS { (Vector2){20, 45} };
	static constexpr Vector2 PLAYER2_STARTING_POS { (Vector2){205, 45} };

	static constexpr Vector2 IDLE_HURTBOX_OFFSETS {(Vector2){35, 14}};
	static constexpr Vector2 IDLE_HURTBOX_DIMENSIONS {(Vector2){30, 81}};
	static constexpr Vector2 CROUCH_HURTBOX_OFFSETS {(Vector2){35, 40}};
	static constexpr Vector2 CROUCH_HURTBOX_DIMENSIONS {(Vector2){30, 60}};
	static constexpr Vector2 FWALK_HURTBOX_OFFSETS {(Vector2){30, 14}};
	static constexpr Vector2 FWALK_HURTBOX_DIMENSIONS {(Vector2){40, 77}};
	static constexpr Vector2 BWALK_HURTBOX_OFFSETS {(Vector2){30, 14}};
	static constexpr Vector2 BWALK_HURTBOX_DIMENSIONS {(Vector2){40, 77}};

	static constexpr float STANDING_POS = 14.0f;
	static constexpr float CROUCHING_POS = 85.0f;

	int roundsWon = 0;

private:
	InputManager m_inputManager {};
	StateMachine m_stateMachine {};

	Hitbox* m_activeHitbox {nullptr};
	Attack* m_activeAttack {nullptr};

	std::vector<Attack*> m_attacks {};

	Texture2D m_sprites;

	bool m_isP1;
	bool m_isBlocking {false};
	bool m_isCrouching {false};

	float m_pushBlockDistance = 0;

	// TODO: Create State to handle this
	void handleMovement(float dt);
};

#endif
