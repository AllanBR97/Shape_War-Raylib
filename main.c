#include "Game.h"

int main(void) {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shape War");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    Run();

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context
    return 0;
}