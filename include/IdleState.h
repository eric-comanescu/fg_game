#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "State.h"
#include "Player.h"

// IDK why i needed a forward declaration here i inclue player (resolve circular dependency?)
class Player;

class IdleState : public State {
public:
	IdleState(Player* player);
	~IdleState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_Idle_State };
	Player* m_player;

	void checkTransitions();
};

#endif
