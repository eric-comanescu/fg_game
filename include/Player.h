#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "Input.h"
#include "StateMachine.h"
#include "WalkingState.h"
#include "IdleState.h"
#include "raylib.h"

enum class Direction {
	Left,
	Right
};

class Player : public GameEntity {
	friend class IdleState;
	friend class WalkingState;

public:
	// TODO: change constructor to protected to avoid instantiation
	Player();
	~Player();

	void update(float dt);
	void render();

private:
	InputManager m_inputManager {};
	StateMachine m_stateMachine {};
	Vector2 m_position {0, 180};

	// TODO: Create State to handle this
	void handleMovement(float dt);
};

#endif
