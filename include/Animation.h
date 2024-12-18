#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

#include "raylib.h"

class Animation {
public:
	Animation(std::vector<Rectangle> frames, int intervalFrames, int cycles = 0);
	~Animation();

	void update(float dt);
	int currentFrame();
	Rectangle currentSprite();
	float duration();
	bool isDone();
	void reset();

private:
	std::vector<Rectangle> m_frames;
	float m_interval;
	float m_timer;
	int m_cycles;

	int m_currentFrame = 0;
	int m_timesPLayed = -1;

};

#endif
