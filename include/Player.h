#ifndef PLAYER_H
#define PLAYER_H

#include "GameEntity.h"
#include "raylib.h"

class Player : public GameEntity {
public:
	Player();
	~Player();

	void update(float dt);
	void render();

private:
	Vector2 position {};
};

#endif
