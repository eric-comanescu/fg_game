#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <unordered_map>

#include "State.h"

class StateMachine {
public:
	StateMachine();
	~StateMachine();

	void add(State* state);
	void change(StateName name);

	void update(float dt);
	void render();

private:
	std::unordered_map<StateName, State*> m_states;
	State* m_currentState;
};

#endif
