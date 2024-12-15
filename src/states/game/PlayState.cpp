#include "../../../include/PlayState.h"
#include "../../../include/State.h"

#include <iostream>

#include "../../../include/Fight.h"
#include "../../../include/raylib.h"

PlayState::PlayState() 
	: State()
	, m_fight((Vector2){0, 180}, (Vector2){50, 90}, (Vector2){430, 180}, (Vector2){50, 90}) {

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

StateName PlayState::name() {
	return m_name;
}
