#include "../../../include/MainMenuState.h"
#include "../../../include/State.h"

#include <iostream>
#include <cassert>

#include "../../../include/StateStack.h"
#include "../../../include/PlayState.h"
#include "../../../include/raylib.h"
#include "../../../include/Game.h"

MainMenuState::MainMenuState(StateStack* sm)
	: State()
	, m_sm {sm} {
	m_buttons.push_back((MainMenuState::Button){
		(Rectangle){30, 90, 50, 30},
		(char*)"Play"
	});
	m_buttons.push_back((MainMenuState::Button){
		(Rectangle){30, 130, 50, 30},
		(char*)"Quit"
	});
}

MainMenuState::~MainMenuState() {

}

void MainMenuState::enter(void* params) {

}

void MainMenuState::exit() {

}

void MainMenuState::update(float dt) {
	m_mousePos = GetMousePosition();

	if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
		if (CheckCollisionRecs(m_buttons[0].bounds, (Rectangle){m_mousePos.x/5.0f, m_mousePos.y/5.0f, 1.0f, 1.0f})) {
			m_sm->push(new PlayState(m_sm), new PlayState::PlayStateEnterParams {
				new Player(Player::PLAYER1_STARTING_POS, Player::DIMENSIONS, true, Hitbox(35, 14, 30, 81)),
				new Player(Player::PLAYER2_STARTING_POS, Player::DIMENSIONS, false, Hitbox(35, 14, 30, 81)),
			});
		}
		else if (CheckCollisionRecs(m_buttons[1].bounds, (Rectangle){m_mousePos.x/5.0f,m_mousePos.y/5.0f,1.0f,1.0f})) {
			Game::shouldClose = true;
		}
	}
}

void MainMenuState::render() {
	DrawTextEx(Game::Font, "Not Another", (Vector2){20, 10}, 36, 1, WHITE);
	DrawTextEx(Game::Font, "Fighting Game", (Vector2){22,40}, 36, 1, WHITE);

	for (auto& button : m_buttons) {
		DrawRectangle(button.bounds.x, button.bounds.y, button.bounds.width, button.bounds.height, DARKGRAY);
		DrawRectangleLines(button.bounds.x, button.bounds.y, button.bounds.width, button.bounds.height, GRAY);

		DrawTextEx(Game::Font, button.text, (Vector2){button.bounds.x + 3, button.bounds.y + 2}, 24, 1, WHITE);
	}
}

StateName MainMenuState::name() {
	return m_name;
}

