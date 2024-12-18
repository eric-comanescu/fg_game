#include "../include/Game.h"

#include <iostream>

#include "../include/StateStack.h"
#include "../include/PlayState.h"
#include "../include/raylib.h"
#include "../include/Player.h"

#include "../include/Fight.h"

Font Game::Font = LoadFont("../src/assets/fonts/alagard.png");

Game::Game(StateStack* stateMachine, int width, int height, int scale)
    : m_stateStack {stateMachine }
    , m_width {width}, m_height {height}, m_scale {scale}
{ this->init(); }

Game::~Game() {
    CloseAudioDevice();
	UnloadRenderTexture(m_canvas);
    CloseWindow();
}

void Game::init() {
    InitWindow(m_width * m_scale, m_height * m_scale, "Gaem");
    InitAudioDevice();

	m_canvas = LoadRenderTexture(m_width, m_height);

	while (!IsRenderTextureReady(m_canvas)) {}

	SetTextureFilter(m_canvas.texture, TEXTURE_FILTER_POINT);

    // SetExitKey(0);
    SetTargetFPS(60);

	m_stateStack->push(new PlayState(m_stateStack), new PlayState::PlayStateEnterParams {
		new Player(Player::PLAYER1_STARTING_POS, Player::STANDING_DIMENSIONS, true, Hitbox()),
		new Player(Player::PLAYER2_STARTING_POS, Player::STANDING_DIMENSIONS, false, Hitbox()),
	});
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
    m_stateStack->update(dt);
}

void Game::render() {
	BeginTextureMode(m_canvas);
	ClearBackground(BLANK);

    m_stateStack->render();

	EndTextureMode();

    BeginDrawing();
    ClearBackground(BLANK);

	DrawTexturePro(
		m_canvas.texture, 																			// Texture to draw
		(Rectangle){ 0.0f, 0.0f, (float)m_canvas.texture.width, -(float)m_canvas.texture.height }, 	// Source Rectangle
		(Rectangle){ 0.0f, 0.0f, (float)(m_width * m_scale), (float)(m_height * m_scale) },			// Destination Rectangle
		(Vector2){ 0.0f, 0.0f },																	// Origin
		0.0f,																						// Rotation
		WHITE																						// Tint
	);

    EndDrawing();
}
