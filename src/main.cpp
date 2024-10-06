#include <cstdlib>

#include "../include/game.h"
#include "../include/StateMachine.h"

constexpr int W_WIDTH = 640;
constexpr int W_HEIGHT = 360;
constexpr int W_SCALE = 2;

StateMachine sm;
Game game(&sm, W_WIDTH, W_HEIGHT, W_SCALE);

int main() {
   game.init();
   game.start();
}
