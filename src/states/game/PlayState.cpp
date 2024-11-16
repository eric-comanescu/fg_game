#include "../../../include/PlayState.h"
#include "../../../include/State.h"

#include <iostream>

#include "../../../include/Fight.h"

PlayState::PlayState() : State{} {

};

PlayState::~PlayState() {

}

void PlayState::enter(void* params) {

}

void PlayState::exit() {

}

void PlayState::update(float dt) {
	m_fight.update(dt);
}

void PlayState::render() {
	m_fight.render();
}
