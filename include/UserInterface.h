#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Player.h"

class UserInterface {
	const static int HP_BAR_WIDTH = 120;
public:
	UserInterface(Player* p1, Player* p2, float* timer);
	~UserInterface();

	void update(float dt);
	void render();
	void reset();

private:
	Player* m_player1;
	Player* m_player2;

	Image m_imBg;
	Texture2D m_texBg;
	int m_bgFrames {0};
	int m_currentBgFrame {0};
	unsigned int m_nextFrameDataOffset;
	float m_bgInterval = 25.0f / 60.0f;
	float m_currentInterval = 0.0f;

	float m_p1HpWidth = UserInterface::HP_BAR_WIDTH;
	float m_p2HpWidth = UserInterface::HP_BAR_WIDTH;

	float m_p1TargetWidth = UserInterface::HP_BAR_WIDTH;
	float m_p2TargetWidth = UserInterface::HP_BAR_WIDTH;

	float* m_timer;

	void updateBg(float dt);
};

#endif
