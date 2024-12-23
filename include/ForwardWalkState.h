#ifndef FORWARD_WALK_STATE_H
#define FORWARD_WALK_STATE_H

#include "State.h"
#include "Player.h"
#include "Direction.h"

class Player;

class ForwardWalkState : public State {
public:
	ForwardWalkState(Player* player);
	~ForwardWalkState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_Forward_Walking_State };
	Player* m_player;

	void checkTransitions();
	void handleMovement(float dt);
};

#endif
