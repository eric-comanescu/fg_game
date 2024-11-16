#include "../../include/StateMachine.h"
#include "../../include/State.h"

#include <iostream>

StateMachine::StateMachine() {

}

StateMachine::~StateMachine() {
	for (auto& x : m_states) {
		delete x.second;
	}
}

void StateMachine::add(State* state) {
	m_states.insert({state->name(), state});
	m_currentState = state;
}

void StateMachine::change(StateName name, void* params = nullptr) {
	m_currentState->exit();
	m_currentState = m_states.at(name);
	m_currentState->enter(params);
}

void StateMachine::update(float dt) {
	m_currentState->update(dt);
}

void StateMachine::render() {
	m_currentState->render();
}
