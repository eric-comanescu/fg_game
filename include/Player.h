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
#include "AttackState.h"
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
	void onHit(Attack * attack);
	const Hitbox& hitbox();

	static constexpr Vector2 CROUCHING_DIMENSIONS { (Vector2){50, 50} };
	static constexpr Vector2 STANDING_DIMENSIONS { (Vector2){50, 90} };

	int roundsWon = 0;

private:
	InputManager m_inputManager {};
	StateMachine m_stateMachine {};

	Hitbox* m_activeHitbox {nullptr};
	Attack* m_activeAttack {nullptr};

	std::vector<Attack*> m_attacks {};

	bool m_isP1;
	bool m_isBlocking {false};

	// TODO: Create State to handle this
	void handleMovement(float dt);
};

#endif
