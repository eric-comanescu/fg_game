#ifndef CROUCH_BLOCK_STATE_H
#define CROUCH_BLOCK_STATE_H

#include "State.h"
#include "Player.h"
#include "Direction.h"
#include "raylib.h"

class Player;

class CrouchBlockState : public State {
public:
	CrouchBlockState(Player* player);
	~CrouchBlockState();

	void enter (void* params = nullptr);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_Crouch_Blocking_State };
	Player* m_player;
	Vector2 m_originalPos;

	void checkTransitions();
};

#endif
