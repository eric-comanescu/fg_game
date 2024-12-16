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
	Attack(Player* player, std::vector<uint8_t> inputs, float duration, uint8_t priority);
	~Attack();

private:
	Player* m_player;
	std::vector<uint8_t> m_inputs;

	float m_duration;
	uint8_t m_priority;
};

#endif
