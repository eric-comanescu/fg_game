#ifndef HITBOX_H
#define HITBOX_H

#include "raylib.h"

class Hitbox {
public:
	Hitbox(float x = 0, float y = 0, float width = 0, float height = 0, Color color = RED);
	~Hitbox();

	void set(float x, float y, float width, float height);
	bool didCollide(const Hitbox& target);
	void render();

	Vector2 position() const;
	Vector2 dimensions() const;

private:
	Vector2 m_position;
	Vector2 m_dimensions;
	Color m_color;
};

#endif
