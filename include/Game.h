#ifndef GAME_H
#define GAME_H

#include "StateMachine.h"
#include "Input.h"

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
	InputManager i {};
    int m_width;
    int m_height;
    int m_scale;

    void gameLoop();
    void update(float dt);
    void render();
};

#endif
