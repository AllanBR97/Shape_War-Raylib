//
// Created by allan on 06/04/24.
//
#include "Meteor.h"
#include "Player.h"
#include "Bullet.h"

void InitPlayer() {
    // Setup player
    p.position = (Vector2){ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f };
    p.rotation = 0.f;

    p.v1 = (Vector2){p.position.x, p.position.y - 20.0f};
    p.v2 = (Vector2){p.position.x - 20.0f, p.position.y + 20.0f};
    p.v3 = (Vector2){p.position.x + 20.0f, p.position.y + 20.0f};

    for (int i = 0; i < MAX_BULLETS; ++i) {
        p.bullets[i].active = false;
        p.bullets[i].position = (Vector2){-100, -100};
    }
}

void RotatePlayer() {
    Vector2 v1 = (Vector2){ p.position.x, p.position.y - 20.0f };
    Vector2 v2 = (Vector2){ p.position.x - 20.0f, p.position.y + 20.0f };
    Vector2 v3 = (Vector2){ p.position.x + 20.0f, p.position.y + 20.0f };

    // Rotate each vertex around the center
    v1 = (Vector2){
            p.position.x + (v1.x - p.position.x) * cosf(p.rotation * DEG2RAD) - (v1.y - p.position.y) * sinf(p.rotation * DEG2RAD),
            p.position.y + (v1.x - p.position.x) * sinf(p.rotation * DEG2RAD) + (v1.y - p.position.y) * cosf(p.rotation * DEG2RAD)
    };

    v2 = (Vector2){
            p.position.x + (v2.x - p.position.x) * cosf(p.rotation * DEG2RAD) - (v2.y - p.position.y) * sinf(p.rotation * DEG2RAD),
            p.position.y + (v2.x - p.position.x) * sinf(p.rotation * DEG2RAD) + (v2.y - p.position.y) * cosf(p.rotation * DEG2RAD)
    };

    v3 = (Vector2){
            p.position.x + (v3.x - p.position.x) * cosf(p.rotation * DEG2RAD) - (v3.y - p.position.y) * sinf(p.rotation * DEG2RAD),
            p.position.y + (v3.x - p.position.x) * sinf(p.rotation * DEG2RAD) + (v3.y - p.position.y) * cosf(p.rotation * DEG2RAD)
    };

    p.v1 = v1;
    p.v2 = v2;
    p.v3 = v3;

    Vector2 direction = GetPlayerDir();
    if (gameStarted) {
        p.position.x += direction.x * PLAYER_SPEED;
        p.position.y += direction.y * PLAYER_SPEED;
    }
}

void Shoot() {
    Vector2 direction = GetPlayerDir();
    p.bullets[indexBullet] = (Bullet){p.v1, direction,true};
    indexBullet = indexBullet < MAX_BULLETS - 1 ? indexBullet + 1 : 0;
}

void DrawPlayer() {
    DrawTriangleLines(p.v1, p.v2, p.v3, YELLOW);
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

void InputPlayer() {
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

inline Vector2 GetPlayerDir() {
    return (Vector2){ sinf(p.rotation * DEG2RAD), -cosf(p.rotation * DEG2RAD) };
}