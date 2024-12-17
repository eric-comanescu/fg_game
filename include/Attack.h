#ifndef ATTACK_H
#define ATTACK_H

#include "AttackState.h"
#include "Player.h"

#include <vector>

class AttackState;
class Player;

class Attack {
	friend class AttackState;
	friend class Player;

public:
	enum AttackStrength {
		Low,
		Medium,
		Strong
	};

	Attack(Player* player, std::vector<uint8_t> inputs, uint8_t frameDuration, 
		AttackStrength attackStrength, bool isLow, uint8_t priority);
	~Attack();

private:
	Player* m_player;
	std::vector<uint8_t> m_inputs;

	float m_duration;
	AttackStrength m_attackStrength;
	bool m_isLow;
	uint8_t m_priority;
};

#endif
