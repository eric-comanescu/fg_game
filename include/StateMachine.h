#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>
#include <list>

#include "State.h"

class StateMachine {
    public:
    StateMachine();
    ~StateMachine();

    void push(State* state, void* params = nullptr);
    void pop();
	const State* top();

    void update(float dt);
    void render();

    private:
	std::list<State*> m_statesList;
    State* m_currentState;
};

#endif
