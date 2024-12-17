#include "../../include/Hitbox.h"

#include <iostream>

#include "../../include/raylib.h"

Hitbox::Hitbox(float x, float y, float width, float height, Color color)
	: m_position {(Vector2){x, y}}
	, m_dimensions {(Vector2){width, height}}
	, m_color {color}
{

}

Hitbox::~Hitbox() {

}

void Hitbox::set(float x, float y, float width, float height) {
	m_position.x = x;
	m_position.y = y;
	m_dimensions.x = width;
	m_dimensions.y = height;
}

bool Hitbox::didCollide(const Hitbox& target) {
	return m_position.x + m_dimensions.x >= target.m_position.x &&
		m_position.x <= target.m_position.x + target.m_dimensions.x &&
		m_position.y + m_dimensions.y >= target.m_position.y &&
		m_position.y <= target.m_position.y + target.m_dimensions.y;
}

Vector2 Hitbox::position() const {
	return m_position;
}

Vector2 Hitbox::dimensions() const {
	return m_dimensions;
}

void Hitbox::render() {
	if (isActive)
		DrawRectangleLines(m_position.x, m_position.y, m_dimensions.x, m_dimensions.y, m_color);
}
