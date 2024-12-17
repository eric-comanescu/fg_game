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
	uint8_t priority
)
	: m_inputs {inputs}
	, m_player {player}
	, m_animation {animation}
	, m_hitboxOffset {hitboxOffsets}
	, m_attackStrength {AttackStrength}
	, m_isLow {isLow}
	, m_priority {priority} {
	m_duration = m_animation->duration();
	m_hitbox.set(
		m_player->m_position.x + m_hitboxOffset.position().x,
		m_player->m_position.y + m_hitboxOffset.position().y,
		m_hitboxOffset.dimensions().x,
		m_hitboxOffset.dimensions().y
	);
}

Attack::~Attack() {
	delete m_animation;
}
