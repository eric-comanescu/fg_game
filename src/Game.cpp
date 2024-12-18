#include "../include/Game.h"

#include <iostream>

#include "../include/StateStack.h"
#include "../include/PlayState.h"
#include "../include/MainMenuState.h"
#include "../include/raylib.h"
#include "../include/Player.h"

#include "../include/Fight.h"

Font Game::Font = LoadFont("../src/assets/fonts/alagard.png");
Sound* Game::Sfx = nullptr;
Sound* Game::Whiff = nullptr;
Sound* Game::Music = nullptr;
bool Game::shouldClose = false;

Game::Game(StateStack* stateMachine, int width, int height, int scale)
    : m_stateStack {stateMachine }
    , m_width {width}, m_height {height}, m_scale {scale}
{ this->init(); }

Game::~Game() {
	UnloadSound(m_sfx);
	UnloadSound(m_whiff);
	UnloadSound(m_music);

    CloseAudioDevice();
	UnloadRenderTexture(m_canvas);
    CloseWindow();
}

void Game::init() {
    InitWindow(m_width * m_scale, m_height * m_scale, "Not Another Fighting Game");
    InitAudioDevice();

	m_canvas = LoadRenderTexture(m_width, m_height);

	while (!IsRenderTextureReady(m_canvas)) {}

	SetTextureFilter(m_canvas.texture, TEXTURE_FILTER_POINT);

    // SetExitKey(0);
    SetTargetFPS(60);

	m_stateStack->push(new MainMenuState(m_stateStack));

	m_sfx = LoadSound("../src/assets/swish_4.wav");
	m_whiff = LoadSound("../src/assets/swish_2.wav");
	m_music = LoadSound("../src/assets/punch_your_way_through.ogg");

	while (!IsSoundReady(m_sfx)) {}
	while (!IsSoundReady(m_whiff)) {}
	while (!IsSoundReady(m_music)) {}

	Game::Sfx = &m_sfx;
	Game::Whiff = &m_whiff;
	Game::Music = &m_music;

	SetSoundVolume(*Game::Sfx, 0.2f);
	SetSoundVolume(*Game::Whiff, 0.2f);
	SetSoundVolume(*Game::Music, 0.02f);
}

void Game::start() {
    gameLoop();
}

void Game::gameLoop() {
    while (!WindowShouldClose() && !Game::shouldClose) {
        float frameTime { GetFrameTime() };
        float dt { frameTime > 0.1f ? 0.1f : GetFrameTime() };

        update(dt);
        render();
    }
}

void Game::update(float dt) {
	if (!IsSoundPlaying(*Game::Music)) {
		PlaySound(*Game::Music);
	}
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
