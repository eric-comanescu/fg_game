#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"
#include "Fight.h"

class PlayState : public State {
public:
	PlayState();
	~PlayState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Play_State };
	Fight m_fight {};
	// UserInterface m_ui;
};

#endif
