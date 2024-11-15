#ifndef GAME_ENTITY_H
#define GAME_ENTITY_H

class GameEntity {
	public:
	GameEntity();
	virtual ~GameEntity() {};

	virtual void update(float dt) = 0;
	virtual void render() = 0;
};

#endif
