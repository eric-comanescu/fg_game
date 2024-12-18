#include "../../../include/PlayState.h"
#include "../../../include/State.h"

#include <iostream>
#include <cassert>

#include "../../../include/Fight.h"
#include "../../../include/UserInterface.h"
#include "../../../include/StateStack.h"
#include "../../../include/raylib.h"

PlayState::PlayState(StateStack* sm) 
	: State()
	, m_sm {sm} {

};

PlayState::~PlayState() {

}

void PlayState::enter(void* params) {
	if (params != nullptr) {
		PlayStateEnterParams* enterParams = reinterpret_cast<PlayStateEnterParams*>(params);

		Player* p1 = enterParams->p1;
		Player* p2 = enterParams->p2;
	
		m_ui = new UserInterface(p1, p2, &m_timer);
		m_fight = new Fight(p1, p2, &m_timer, m_sm, m_ui);

		delete enterParams;
	}
	else {
		assert(m_fight != nullptr && "Pass in a PlayStateEnterParams when first initializing PlayState");
		m_fight->reset();
	}
}

void PlayState::exit() {

}

void PlayState::update(float dt) {
	m_ui->update(dt);
	m_fight->update(dt);
}

void PlayState::render() {
	m_ui->render();
	m_fight->render();
}

StateName PlayState::name() {
	return m_name;
}
