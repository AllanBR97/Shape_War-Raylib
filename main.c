#include "Game.h"

const int screenWidth = 800;
const int screenHeight = 600;

bool gameStarted = false;
Player player;

void update() {
    UpdateBullet(&player);
    WrapScreen(&player);
    InputPlayer(&player);
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawPlayer(&player);
    DrawBullet(&player);
    EndDrawing();
}

int main(void) {
    // Initialization
    //--------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "Shape War");
    InitPlayer(&player);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) {
        // Update
        update();

        // Draw
        //----------------------------------------------------------------------------------
        draw();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}