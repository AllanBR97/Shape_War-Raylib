#include "Game.h"

const int screenWidth = 800;
const int screenHeight = 800;

bool gameStarted = false;
Player player;
Meteor meteor;

void update() {
    UpdateBullet(&player);
    UpdateMeteor(&meteor);
    WrapScreen(&player);
    InputPlayer(&player);
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawPlayer(&player);
    DrawBullet(&player);
    DrawMeteor(&meteor);
    EndDrawing();
}

void SetupGame() {
    InitPlayer(&player);
    InitMeteor(&meteor);
}

int main(void) {
    // Initialization
    InitWindow(screenWidth, screenHeight, "Shape War");
    SetupGame();

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    // Main game loop
    while (!WindowShouldClose()) {
        update();
        draw();
    }

    // De-Initialization
    CloseWindow();        // Close window and OpenGL context

    return 0;
}