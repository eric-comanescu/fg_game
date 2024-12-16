#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Input.h"
#include "StateMachine.h"
#include "ForwardWalkState.h"
#include "BackwardsWalkState.h"
#include "IdleState.h"
#include "CrouchState.h"
#include "Direction.h"
#include "Hitbox.h"
#include "raylib.h"

class Fight;

class Player : public GameEntity {
	friend class IdleState;
	friend class ForwardWalkState;
	friend class BackwardsWalkState;
	friend class CrouchState;

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
	const Hitbox& hitbox();

private:
	InputManager m_inputManager {};
	StateMachine m_stateMachine {};

	bool m_isP1;

	// TODO: Create State to handle this
	void handleMovement(float dt);
};

#endif
