#ifndef ANIMATION_H
#define ANIMATION_H

#include <vector>

class Animation {
public:
	Animation(std::vector<int> frames, int intervalFrames, int cycles = 0);
	~Animation();

	void update(float dt);
	int currentFrame();
	float duration();
	bool isDone();
	void reset();

private:
	std::vector<int> m_frames;
	float m_interval;
	float m_timer;
	int m_cycles;

	int m_currentFrame = 0;
	int m_timesPLayed = -1;

};

#endif
