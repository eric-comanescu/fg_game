#ifndef MOVING_STATE_H
#define MOVING_STATE_H

#include "State.h"
#include "Player.h"

class Player;
enum class Direction;

class WalkingState : public State {
public:
	WalkingState(Player* player);
	~WalkingState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_Walking_State };
	Direction m_walkingDirection;
	Player* m_player;

	void checkTransitions();
	void handleMovement(float dt);
};

#endif
