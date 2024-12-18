#ifndef FIGHT_H
#define FIGHT_H

#include "Player.h"
#include "GameEntity.h"
#include "raylib.h"
#include "StateStack.h"
#include "UserInterface.h"

#include <vector>

class Fight {
public:
	Fight(Player* p1, Player* p2, float* timer, StateStack* sm, UserInterface* ui);
	~Fight();

	void update(float dt);
	void render();
	void reset();

private:
	// TODO: Change to pointers when implementing characters
	Player* m_player1;
	Player* m_player2;
	std::vector<GameEntity*> m_entities;
	StateStack* m_sm;
	UserInterface* m_ui;

	float* m_timer;

	void setPlayerDirections();
	void updateEntities(float dt);
	void updatePlayer(float dt, Player& player);
	void handleRoundEnd();
};

#endif
