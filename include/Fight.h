#ifndef FIGHT_H
#define FIGHT_H

#include "Player.h"
#include "GameEntity.h"
#include "raylib.h"
#include <vector>

class Fight {
public:
	Fight(Vector2 player1Pos, Vector2 p1Dims, Vector2 player2Pos, Vector2 p2Dims);
	~Fight();

	void update(float dt);
	void render();

private:
	// TODO: Change to pointers when implementing characters
	Player* m_player1;
	Player* m_player2;
	std::vector<GameEntity*> m_entities;

	void setPlayerDirections();
	void updateEntities(float dt);
	void updatePlayer(float dt, Player& player);
};

#endif
