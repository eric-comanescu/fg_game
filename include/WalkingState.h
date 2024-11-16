#ifndef MOVING_STATE_H
#define MOVING_STATE_H

#include "State.h"
#include "Player.h"

class Player;

class WalkingState : public State {
public:
	struct EnterParams {
		Player::Direction direction;
	};

	WalkingState(Player* player);
	~WalkingState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Walking_State };
	Player::Direction m_movementDirection;
	Player* m_player;

	void checkTransitions();
};

#endif
