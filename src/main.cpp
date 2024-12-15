#include "../include/Game.h"
#include "../include/StateMachine.h"
#include "../include/Input.h"
#include "../include/PlayState.h"

constexpr int WINDOW_WIDTH = 480;
constexpr int WINDOW_HEIGHT = 270;
constexpr int WINDOW_SCALE = 3;

StateStack sm {};
Game game(&sm, WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_SCALE);

int main() {
	game.start();
}
