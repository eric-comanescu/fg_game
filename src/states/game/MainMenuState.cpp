#include "../../../include/MainMenuState.h"
#include "../../../include/State.h"

#include <iostream>
#include <cassert>

#include "../../../include/StateStack.h"
#include "../../../include/raylib.h"

MainMenuState::MainMenuState(StateStack* sm)
	: State()
	, m_sm {sm} {

}

MainMenuState::~MainMenuState() {

}

void MainMenuState::enter(void* params) {

}

void MainMenuState::exit() {

}

void MainMenuState::update(float dt) {

}

void MainMenuState::render() {

}

StateName MainMenuState::name() {
	return m_name;
}

