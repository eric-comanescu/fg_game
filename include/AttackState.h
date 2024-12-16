#ifndef ATTACK_STATE_H
#define ATTACK_STATE_H

#include "State.h"
#include "Attack.h"
#include "Player.h"
#include "Direction.h"
#include "raylib.h"

class Player;

class AttackState : public State {
public:
	AttackState(Player* player);
	~AttackState();

	void enter(void* params = nullptr);
	void exit();
	void update(float dt);
	void render();

	StateName name();

private:
	StateName m_name { StateName::Player_Attack_State };
	Player* m_player;
	Attack* m_attack;

	void checkTranstions();
};

#endif
