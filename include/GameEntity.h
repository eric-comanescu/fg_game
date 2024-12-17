#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

#include "Hitbox.h"
#include "raylib.h"

class Player;

class GameEntity {
	friend class Player;
	public:
	GameEntity();
	virtual ~GameEntity() {};

	virtual void update(float dt) = 0;
	virtual void render() = 0;
	virtual bool didCollideWith(const Hitbox& target) = 0;
	virtual void onCollision(GameEntity* collider) = 0;
	virtual const Hitbox& hitbox() = 0;

	float maxHp {200};
	float hp {200};

	bool isDead {false};

protected:
	Vector2 m_position {};
	Vector2 m_prevPosition {};
	Vector2 m_dimensions {};

	Hitbox m_hurtbox {};
	Hitbox m_hurtboxOffsets {};
};

#endif
