#ifndef PLAYSTATE_H
#define PLAYSTATE_H

#include "State.h"

class PlayState : public State {
public:
	PlayState();
	~PlayState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

private:
	// Fight m_fight;
	// UserInterface m_ui;
};

#endif
