#ifndef GAME_H
#define GAME_H

#include "../include/StateMachine.h"

class Game {
    public:
    Game() = delete;
    Game(StateMachine* stateMachine, int width, int height, int scale);
    ~Game();

    void init();
    void start();

    private:
    // Not heap allocated, no need to free
    StateMachine* m_stateMachine;
    int m_width;
    int m_height;
    int m_scale;

    void gameLoop();
    void update(float dt);
    void render();
};

#endif
