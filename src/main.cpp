#include "../include/raylib.h"

constexpr int W_WIDTH = 640;
constexpr int W_HEIGHT = 360;
constexpr int W_SCALE = 2;

int main() {
    InitWindow(W_WIDTH * W_SCALE, W_HEIGHT * W_SCALE, "Gaem");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);
        DrawText("Test", 0, 0, 24, LIGHTGRAY);

        EndDrawing();
    }

    CloseWindow();
}
