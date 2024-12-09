#ifndef GAME_H
#define GAME_H

#include "StateStack.h"
#include "Input.h"
#include "raylib.h"

class Game {
    public:
    Game() = delete;
    Game(StateStack* stateMachine, int width, int height, int scale);
    ~Game();

    void init();
    void start();

    private:
	RenderTexture2D m_canvas;
	InputManager i {};

    // Not heap allocated, no need to free
    StateStack* m_stateMachine;

    int m_width;
    int m_height;
    int m_scale;

    void gameLoop();
    void update(float dt);
    void render();
};

#endif
