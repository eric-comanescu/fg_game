#ifndef STATE_MACHINE_H
#define STATE_MACHINE_H

#include <vector>

#include "State.h"

class StateMachine {
    public:
    StateMachine();
    ~StateMachine();

    void add(State* state);
    void change(char* name); // TODO: Add enter params to method when implemented
    void update(float dt);
    void render();

    private:
    // Dont need to free m_states and m_currentState, not heap allocated
    std::vector<State*> m_states;
    State* m_currentState;
};

#endif
