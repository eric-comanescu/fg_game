#include "../../include/StateMachine.h"

#include <typeinfo>
#include <string.h>
#include <cassert>

#include "../../include/PlayState.h"
#include "../../include/State.h"

StateMachine::StateMachine()
    : m_currentState {nullptr} 
{
	// TODO: Change this to main menu state
	this->push(new PlayState());
}

StateMachine::~StateMachine() {
	while (!m_statesList.empty()) {
		State* removedState = m_statesList.back();
		m_statesList.pop_back();

		delete removedState;
	}
}

void StateMachine::push(State* state, void* params) {
	m_statesList.push_back(state);
	m_statesList.back()->enter(params);
}

void StateMachine::pop() {
	m_statesList.back()->exit();

	State* removedState = m_statesList.back();
	m_statesList.pop_back();

	delete removedState;
}

const State* StateMachine::top() {
	return m_statesList.back();
}

void StateMachine::update(float dt) {
	assert(!m_statesList.empty() && "State machine should never be empty.");

	m_statesList.back()->update(dt);
}

void StateMachine::render() {
	assert(!m_statesList.empty() && "State machine should never be empty.");

	for (State* state : m_statesList) {
		state->render();
	}
}
