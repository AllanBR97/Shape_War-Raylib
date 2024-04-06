//
// Created by allan on 27/09/23.
//
#include "Game.h"
#include "Meteor.h"
#include "Player.h"
#include "Bullet.h"

int indexBullet;
bool gameStarted;
Player p;

// Main game loop
void Run() {
    SetupGame();
    while (!WindowShouldClose()) {
        Update();
        Draw();
    }
}

void Update() {
    UpdateBullet();
    UpdateMeteor();
    RotatePlayer();
    ScreenWrap();
    InputPlayer();
}

void Draw() {
    BeginDrawing();
    ClearBackground(BLACK);
    DrawPlayer();
    DrawBullet();
    DrawMeteor();
    DrawGamePause();
    EndDrawing();
}

void SetupGame() {
    indexBullet = 0;
    gameStarted = true;
    InitPlayer();
    InitMeteor();
}

void DrawGamePause() {
    if (!gameStarted) {
        DrawText("PRESS UP TO START", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 30, RED);
    }
}