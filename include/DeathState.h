#ifndef DEATH_STATE_H
#define DEATH_STATE_H

#include "State.h"
#include "Player.h"
#include "Animation.h"

class Player;

class DeathState : public State {
public:
	DeathState(Player* player);
	~DeathState();

	void enter(void* params = nullptr);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_Death_State };
	Animation* m_animation;
	Player* m_player;

	void checkTransitions();
};

#endif
