#include "../../include/StateMachine.h"

#include <typeinfo>
#include <string.h>
#include <cassert>

#include "../../include/PlayState.h"
#include "../../include/State.h"

StateMachine::StateMachine()
    : m_currentState {nullptr} 
{
	this->add(new PlayState());
}

StateMachine::~StateMachine() {
	for (auto const& state : m_states) {
		delete state;
	}
}

void StateMachine::add(State* state) {
    m_states.push_back(state);
}

void StateMachine::change(char* name) {
    // m_currentState = m_states[name];
	for (int i = 0; i < m_states.size(); i++) {
		if (strcmp(name, m_states[i]->m_name) == 0) {
			m_currentState = m_states[i];
			return;
		}
	}

	assert(false && "Check state name for typos, could not be found");
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
