#include "../include/Game.h"
#include "../include/StateMachine.h"
#include "../include/Input.h"

constexpr int WIDTH = 640;
constexpr int HEIGHT = 360;
constexpr int SCALE = 2;

StateMachine sm {};
InputManager i;
Game game(&sm, WIDTH, HEIGHT, SCALE);

int main() {
	i.getInput();
	game.start();
}
