#ifndef IDLE_STATE_H
#define IDLE_STATE_H

#include "State.h"
#include "Player.h"
#include "StateMachine.h"

// IDK why i needed a forward declaration here
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
	StateName m_name { StateName::PlayerIdleState };
	Player* m_player;
};

#endif
