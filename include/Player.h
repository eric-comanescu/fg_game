#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Input.h"
#include "StateMachine.h"
#include "ForwardWalkState.h"
#include "BackwardsWalkState.h"
#include "IdleState.h"
#include "Direction.h"
#include "raylib.h"

class Fight;

class Player : public GameEntity {
	friend class IdleState;
	friend class ForwardWalkState;
	friend class BackwardsWalkState;

	friend class Fight;
public:
	Direction facing {};

	// TODO: change constructor to protected to avoid instantiation
	Player(Vector2 pos, bool isP1);
	~Player();

	void update(float dt);
	void render();

private:
	InputManager m_inputManager {};
	StateMachine m_stateMachine {};
	Vector2 m_position {0, 180};

	bool m_isP1;

	// TODO: Create State to handle this
	void handleMovement(float dt);
};

#endif
