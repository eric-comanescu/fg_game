#include "../../include/Animation.h"

#include <vector>

Animation::Animation(std::vector<int> frames, int intervalFrames, int cycles)
	: m_frames {frames}
	, m_interval {static_cast<float>(intervalFrames) / 60.0f} 
	, m_timer {m_interval}
	, m_cycles {cycles} {

}

Animation::~Animation() {

}

void Animation::update(float dt) {
	if (m_frames.size() == 1)
		return;
	
	m_timer -= dt; 
	if (m_timer > 0)
		return;
	
	m_timer = m_interval;

	if (m_currentFrame == 0)
		m_timesPLayed++;

	m_currentFrame = (m_currentFrame + 1) % m_frames.size();
}

int Animation::currentFrame() {
	return m_currentFrame;
}

float Animation::duration() {
	return m_interval * static_cast<float>(m_frames.size());
}

bool Animation::isDone() {
	return m_timesPLayed == m_cycles;
}

void Animation::reset() {
	m_currentFrame = 0;
	m_timesPLayed = -1;
}
