#include "../../../include/WalkingState.h"

#include "../../../include/Player.h"
#include "../../../include/Input.h"
#include "../../../include/State.h"

WalkingState::WalkingState(Player* player)
	: State {},
	m_player {player}
{}

WalkingState::~WalkingState() {

}

void WalkingState::enter(void* params = nullptr) {
	constexpr uint8_t LEFT_BITMASK = 0b00000010;
	constexpr uint8_t RIGHT_BITMASK = 0b00000001;

	const std::list<InputManager::Input>& inputs { m_player->m_inputManager.getInputList() };

	if ((inputs.back().directionHold & LEFT_BITMASK) > 0) {
		m_movementDirection = Player::Direction::Left;
	}

	if ((inputs.back().directionHold & RIGHT_BITMASK) > 0) {
		m_movementDirection = Player::Direction::Right;
	}
}

void WalkingState::exit() {

}

void WalkingState::update(float dt) {

}

void WalkingState::render() {

}

StateName WalkingState::name() {
	return m_name;
}
