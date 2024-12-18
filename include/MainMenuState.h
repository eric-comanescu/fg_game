#ifndef MAIN_MENU_STATE_H
#define MAIN_MENU_STATE_H

#include "State.h"
#include "StateStack.h"

class MainMenuState : public State {
public:
	MainMenuState(StateStack* sm);
	~MainMenuState();

	void enter(void* params = nullptr);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Main_Menu_State };

	StateStack* m_sm;
};

#endif
