#include "../../include/Attack.h"

#include <vector>

#include "../../include/Player.h"
#include "../../include/Animation.h"
#include "../../include/Hitbox.h"

Attack::Attack(
	Player* player, 
	Animation* animation,
	std::vector<uint8_t> inputs,
	Hitbox hitboxOffsets,
	AttackStrength AttackStrength, 
	bool isLow, 
	float damage,
	uint8_t priority
)
	: m_inputs {inputs}
	, m_player {player}
	, m_animation {animation}
	, m_hitboxOffset {hitboxOffsets}
	, m_attackStrength {AttackStrength}
	, m_isLow {isLow}
	, m_damage {damage}
	, m_priority {priority} {
	m_duration = m_animation->duration();
}

Attack::~Attack() {
	delete m_animation;
}
