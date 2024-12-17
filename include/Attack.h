#ifndef ATTACK_H
#define ATTACK_H

#include "AttackState.h"
#include "Player.h"
#include "Animation.h"
#include "Hitbox.h"

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

	Attack(
		Player* player, 
		Animation* animation, 
		std::vector<uint8_t> inputs, 
		Hitbox hitboxOffset,
		AttackStrength attackStrength, 
		bool isLow, 
		uint8_t priority
	);
	~Attack();

private:
	Player* m_player;
	Animation* m_animation;
	std::vector<uint8_t> m_inputs;

	Hitbox m_hitbox;
	Hitbox m_hitboxOffset;

	AttackStrength m_attackStrength;
	uint8_t m_priority;
	float m_duration;
	bool m_isLow;
};

#endif
