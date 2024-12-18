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

	static Font Font;
	static Sound* Sfx;
	static Sound* Whiff;
	static Sound* Music;
	static bool shouldClose;

    private:
	RenderTexture2D m_canvas;

	Sound m_sfx;
	Sound m_whiff;
	Sound m_music;

    // Not heap allocated, no need to free
    StateStack* m_stateStack;

    int m_width;
    int m_height;
    int m_scale;

    void gameLoop();
    void update(float dt);
    void render();
};

#endif
