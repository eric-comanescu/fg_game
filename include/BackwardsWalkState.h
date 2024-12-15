#ifndef BACK_WALK_STATE_H
#define BACK_WALK_STATE_H

#include "State.h"
#include "Player.h"
#include "Direction.h"

class Player;

class BackwardsWalkState : public State {
public:
	BackwardsWalkState(Player* player);
	~BackwardsWalkState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_Backwards_Walking_State };
	Player* m_player;

	void checkTransition();
	void handleMovement(float dt);
};

#endif
