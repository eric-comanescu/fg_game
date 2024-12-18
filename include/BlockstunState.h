#ifndef BLOCKSTUN_STATE_H
#define BLOCKSTUN_STATE_H

#include "State.h"
#include "Player.h"
#include "Direction.h"
#include "raylib.h"

class Player;

class BlockstunState : public State {
public:
	BlockstunState(Player* player);
	~BlockstunState();

	void enter(void* params = nullptr);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_BlockStun_State };
	Player* m_player;

	float m_duration;

	void checkTransitions();
};

#endif
