#ifndef ROUND_INTRO_STATE_H
#define ROUND_INTRO_STATE_H

#include "State.h"
#include "Player.h"
#include "UserInterface.h"
#include "StateStack.h"
#include "Fight.h"

class RoundIntroState : public State {
	friend class StateStack;

public:
	RoundIntroState(StateStack* sm);
	~RoundIntroState();

	void enter(void* params);
	void exit();
	void update(float dt);
	void render();

	StateName name();

	struct RoundIntroEnterParams {
		Fight* fight;
		UserInterface* ui;
		Player* p1;
		Player* p2;
	};

private:
	StateName m_name { StateName::Round_Intro_State };
	Fight* m_fight;
	UserInterface* m_ui;
	Player* m_p1;
	Player* m_p2;

	float m_timer {3.0f};
	float m_tweenTimer {1.0f};
	float m_reverseTimer {0.0f};
	float m_fadeDelay {0.5f};

	bool m_startTween {false};
	bool m_undoTween {false};
	bool m_shouldPop {false};
	bool m_singleUpdate {false};
	bool m_drawWinnerText {false};

	int m_roundNumber;

	StateStack* m_sm;
};

#endif
