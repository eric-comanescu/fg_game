#ifndef ROUND_INTRO_STATE_H
#define ROUND_INTRO_STATE_H

#include "State.h"
#include "Player.h"
#include "UserInterface.h"
#include "StateStack.h"

class RoundIntroState : public State {
public:
	RoundIntroState(StateStack* sm);
	~RoundIntroState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

	struct RoundIntroEnterParams {
		UserInterface* ui;
		Player* p1;
		Player* p2;
		int winner;
	};

private:
	StateName m_name { StateName::Round_Intro_State };
	UserInterface* m_ui;
	Player* m_p1;
	Player* m_p2;
	int m_winner;

	float m_timer {3.0f};

	int m_roundNumber;

	StateStack* m_sm;
};

#endif
