#include "Game.h"
#include "Meteor.h"
#include "Player.h"
#include "Bullet.h"

void update() {
    UpdateBullet();
    UpdateMeteor();
    RotatePlayer();
    ScreenWrap();
    InputPlayer();
}

void draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawPlayer();
    DrawBullet();
    DrawMeteor();
    DrawGamePause();
    EndDrawing();
}

int main(void) {
    // Initialization
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shape War");
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