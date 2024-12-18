#include "../../include/StateStack.h"

#include <typeinfo>
#include <string.h>
#include <cassert>
#include <iostream>

#include "../../include/PlayState.h"
#include "../../include/State.h"
#include "../../include/RoundIntroState.h"

StateStack::StateStack()
    : m_currentState {nullptr} 
{}

StateStack::~StateStack() {
	while (!m_statesList.empty()) {
		State* removedState = m_statesList.back();
		m_statesList.pop_back();

		delete removedState;
	}
}

void StateStack::push(State* state, void* params) {
	m_statesList.push_back(state);
	m_statesList.back()->enter(params);
}

void StateStack::pop() {
	m_statesList.back()->exit();

	State* removedState = m_statesList.back();

	m_statesList.pop_back();

	m_statesList.back()->enter(nullptr);

	std::cout << static_cast<int>(m_statesList.back()->name()) << '\n';

	delete removedState;
}

const State* StateStack::top() {
	return m_statesList.back();
}

void StateStack::update(float dt) {
	assert(!m_statesList.empty() && "State machine should never be empty.");

	m_statesList.back()->update(dt);
}

void StateStack::render() {
	assert(!m_statesList.empty() && "State machine should never be empty.");

	for (State* state : m_statesList) {
		state->render();
	}
}
