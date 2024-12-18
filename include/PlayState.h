#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "Fight.h"
#include "UserInterface.h"
#include "StateStack.h"
#include "Player.h"

class PlayState : public State {
public:
	PlayState(StateStack* sm);
	~PlayState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

	struct PlayStateEnterParams {
		Player* p1;
		Player* p2;
	};

private:
	StateName m_name { StateName::Play_State };
	Fight* m_fight;
	UserInterface* m_ui;

	StateStack* m_sm;

	float m_timer {99.9f};
};

#endif
