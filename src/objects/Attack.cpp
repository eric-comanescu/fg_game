#include "../../include/Attack.h"

#include <vector>

#include "../../include/Player.h"

Attack::Attack(Player* player, std::vector<uint8_t> inputs, uint8_t frameDuration
	, AttackStrength AttackStrength, bool isLow, uint8_t priority)
	: m_inputs {inputs}
	, m_player {player}
	, m_duration {static_cast<float>(frameDuration) / 60.0f}
	, m_attackStrength {AttackStrength}
	, m_isLow {isLow}
	, m_priority {priority} {

}

Attack::~Attack() {

}
