#ifndef FIGHT_H
#define FIGHT_H

#include "Player.h"
#include "raylib.h"
#include <vector>

class Fight {
public:
	Fight(Vector2 player1Pos, Vector2 player2Pos);
	~Fight();

	void update(float dt);
	void render();

private:
	// TODO: Change to pointers when implementing characters
	//! SEGFAULT WHEN UNCOMMENTING PLAYER MEMBERS (WHY???)
	Player m_player1;
	Player m_player2;
};

#endif
