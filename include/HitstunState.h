#ifndef HITSTUN_STATE_H
#define HITSTUN_STATE_H

#include "State.h"
#include "Player.h"
#include "Direction.h"
#include "raylib.h"

class Player;

class HitstunState : public State {
public:
	HitstunState(Player* player);
	~HitstunState();

	void enter(void* params = nullptr);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_HitStun_State };
	Player* m_player;

	float m_duration;

	void checkTransitions();
};

#endif
