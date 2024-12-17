#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include "Player.h"

class UserInterface {
	const static int HP_BAR_WIDTH = 120;
public:
	UserInterface(Player* p1, Player* p2);
	~UserInterface();

	void update(float dt);
	void render();

private:
	Player* m_player1;
	Player* m_player2;

	float m_p1HpWidth;
	float m_p2HpWidth;
};

#endif
