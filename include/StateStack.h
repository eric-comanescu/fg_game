#ifndef STATE_STACK_H
#define STATE_STACK_H

#include <vector>
#include <list>

#include "State.h"

class StateStack {
    public:
    StateStack();
    ~StateStack();

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
