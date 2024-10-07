#include "../include/game.h"
#include "../include/StateMachine.h"

constexpr int WIDTH = 640;
constexpr int HEIGHT = 360;
constexpr int SCALE = 2;

StateMachine sm;
Game game(&sm, WIDTH, HEIGHT, SCALE);

int main() {
   game.init();
   game.start();
}
