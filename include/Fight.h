#ifndef FIGHT_H
#define FIGHT_H

#include "Player.h"
#include <vector>

class Fight {
public:
	Fight();
	~Fight();

	void update(float dt);
	void render();

private:
	// TODO: Change to pointers when implementing characters
	//! SEGFAULT WHEN UNCOMMENTING PLAYER MEMBERS (WHY???)
	Player m_player1 {};
	// Player m_player2 {};
};

#endif
