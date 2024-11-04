#include "../../../include/PlayState.h"
#include "../../../include/State.h"

#include <iostream>

PlayState::PlayState() : State{} {

};

PlayState::~PlayState() {
	std::cout << "called playstate destructor\n";
}

void PlayState::enter(void* params) {

}

void PlayState::exit() {

}

void PlayState::update(float dt) {

}

void PlayState::render() {

}
