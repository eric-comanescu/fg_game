#include "../../include/StateMachine.h"
#include "../../include/State.h"

StateMachine::StateMachine() {

}

StateMachine::~StateMachine() {

}

void StateMachine::add(State* state) {
	m_states.insert({state->name(), state});
	m_currentState = state;
}

void StateMachine::change(StateName name, void* params) {
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
