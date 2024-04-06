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
    HandleInput();
    UpdateBullet();
    UpdateMeteor();
    UpdatePlayer();
    ScreenWrap();
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

void Shoot() {
    Vector2 direction = GetPlayerDir();
    p.bullets[indexBullet] = (Bullet){p.v1, direction,true};
    indexBullet = indexBullet < MAX_BULLETS - 1 ? indexBullet + 1 : 0;
}

void ScreenWrap() {
    // Verifica o tamanho do jogador
    float playerHalfWidth = 20;
    float playerHalfHeight = 20;
    float meteorHalfWidth, meteorHalfHeight;

    // Verifica o tamanho do meteoro
    for (int i = 0; i < BIG_METEORS; ++i) {
        meteorHalfWidth = meteor[i].radius;
        meteorHalfHeight = meteor[i].radius;
    }

    // Check if player is beyond the right edge
    if (p.position.x > SCREEN_WIDTH + playerHalfWidth) {
        p.position.x = -playerHalfWidth;
    }
        // Check if player is beyond the left edge
    else if (p.position.x < -playerHalfWidth) {
        p.position.x = SCREEN_WIDTH + playerHalfWidth;
    }

    // Check if player is beyond the bottom edge
    if (p.position.y > SCREEN_HEIGHT + playerHalfHeight) {
        p.position.y = -playerHalfHeight;
    }
        // Check if player is beyond the top edge
    else if (p.position.y < -playerHalfHeight) {
        p.position.y = SCREEN_HEIGHT + playerHalfHeight;
    }

    for (int i = 0; i < BIG_METEORS; ++i) {
        // Check if meteor is beyond the right edge
        if (meteor[i].position.x > SCREEN_WIDTH + meteorHalfWidth) {
            meteor[i].position.x = -meteorHalfWidth;
        }
            // Check if meteor is beyond the left edge
        else if (meteor[i].position.x < -meteorHalfWidth) {
            meteor[i].position.x = SCREEN_WIDTH + meteorHalfWidth;
        }
        // Check if meteor is beyond the bottom edge
        if (meteor[i].position.y > SCREEN_HEIGHT + meteorHalfHeight) {
            meteor[i].position.y = -meteorHalfHeight;
        }
            // Check if meteor is beyond the top edge
        else if (meteor[i].position.y < 0 - meteorHalfHeight) {
            meteor[i].position.y = SCREEN_HEIGHT + meteorHalfHeight;
        }
    }
}

void HandleInput() {
    if (IsKeyDown(KEY_UP)) gameStarted = true;

    if (gameStarted) {
        if (IsKeyDown(KEY_RIGHT)) p.rotation += ROTATION_SPEED;

        else if (IsKeyDown(KEY_LEFT)) p.rotation -= ROTATION_SPEED;

        if (IsKeyReleased(KEY_SPACE)) {
            Shoot();
        }

        if (IsKeyDown(KEY_DOWN)) gameStarted = false;
    }
}