#include "../../include/Attack.h"

#include <vector>

#include "../../include/Player.h"

Attack::Attack(Player* player, std::vector<uint8_t> inputs, float duration, uint8_t priority)
	: m_inputs {inputs}
	, m_player {player}
	, m_duration {duration}
	, m_priority {priority} {

}

Attack::~Attack() {

}
