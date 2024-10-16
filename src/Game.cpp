#include "../include/Game.h"
#include "../include/StateMachine.h"
#include "../include/raylib.h"

Game::Game(StateMachine* stateMachine, int width, int height, int scale)
    : m_stateMachine {stateMachine}
    , m_width {width}, m_height {height}, m_scale {scale}
{ this->init(); }

Game::~Game() {
	CloseAudioDevice();
	CloseWindow();
}

void Game::init() {
    InitWindow(m_width * m_scale, m_height * m_scale, "Gaem");
	InitAudioDevice();
    SetExitKey(0);
    SetTargetFPS(120);
}

void Game::start() {
    gameLoop();
}

void Game::gameLoop() {
    while (!WindowShouldClose()) {
		float frameTime { GetFrameTime() };
        float dt { frameTime > 0.1f ? 0.1f : GetFrameTime() };

        update(dt);
        render();
    }
}

void Game::update(float dt) {
    m_stateMachine->update(dt);
}

void Game::render() {
    BeginDrawing();
    ClearBackground(BLANK);
	DrawFPS(0, 0);

    m_stateMachine->render();

    EndDrawing();
}
