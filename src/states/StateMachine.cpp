#include "../../include/StateMachine.h"

StateMachine::StateMachine()
    : m_currentState {nullptr}
{}

StateMachine::~StateMachine() {}

void StateMachine::add(State* state) {
    m_states.insert({state->m_name, state});
}

void StateMachine::change(char* name) {
    m_currentState = m_states[name];
}

void StateMachine::update(float dt) {
    if (m_currentState != nullptr) {
        m_currentState->update(dt);
    }
}

void StateMachine::render() {
    if (m_currentState != nullptr) {
        m_currentState->render();
    }
}
