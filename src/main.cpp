#include "../include/raylib.h"

#include <cstdlib>

constexpr int W_WIDTH = 640;
constexpr int W_HEIGHT = 360;
constexpr int W_SCALE = 2;

int main() {
    InitWindow(W_WIDTH * W_SCALE, W_HEIGHT * W_SCALE, "Gaem");
    SetExitKey(0);
    SetTargetFPS(60);

    // TODO: if def __WIN32 (or __CYGWIN__ ?) cd to $home_dir\appdata\local and make folder else cd to .local and make folder there
    // also include <filesystem> and check cpp reference for std::filesystem functions

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(BLANK);
        DrawFPS(0, 0);

        if (IsKeyDown(KEY_W)) {
            #ifdef linux
            DrawText(getenv("HOME"), 0, 20, 24, WHITE);
            #endif

            #ifdef __WIN32
            DrawText(getenv("LOCALAPPDATA"), 0, 20, 24, WHITE)
            #endif
        }

        EndDrawing();
    }

    CloseWindow();
}
