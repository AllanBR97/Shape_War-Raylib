//
// Created by allan on 27/09/23.
//
#include "Game.h"

int countBullets = 0;

bool gameStarted;
Player p;
Meteor meteor;

void SetupGame() {
    gameStarted = true;
    InitPlayer();
    InitMeteor();
}

void InitPlayer() {
    // Setup player
    p.position = (Vector2){ (float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f };
    p.rotation = 0.0f;

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
    for (int i = 0; i < MAX_BULLETS; ++i) {
        p.bullets[i] = (Bullet){p.v1, direction,true};
    }
    countBullets = countBullets > 3 ? 0 : countBullets + 1;
}

void DrawPlayer() {
    DrawTriangleLines(p.v1, p.v2, p.v3, YELLOW);
}

void ScreenWrap() {
    // Verifica o tamanho do jogador
    float playerHalfWidth = 20;
    float playerHalfHeight = 20;

    // Verifica o tamanho do meteoro
    float meteorHalfWidth = meteor.radius;
    float meteorHalfHeight = meteor.radius;

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

    // Check if meteor is beyond the right edge
    if (meteor.position.x > SCREEN_WIDTH + meteorHalfWidth) {
        meteor.position.x = -meteorHalfWidth;
    }
        // Check if meteor is beyond the left edge
    else if (meteor.position.x < -meteorHalfWidth) {
        meteor.position.x = SCREEN_WIDTH + meteorHalfWidth;
    }

    // Check if meteor is beyond the bottom edge
    if (meteor.position.y > SCREEN_HEIGHT + meteorHalfHeight) {
        meteor.position.y = -meteorHalfHeight;
    }
        // Check if meteor is beyond the top edge
    else if (meteor.position.y < 0 - meteorHalfHeight) {
        meteor.position.y = SCREEN_HEIGHT + meteorHalfHeight;
    }
}

void InputPlayer() {
    if (IsKeyDown(KEY_UP)) gameStarted = true;

    if (gameStarted) {
        if (IsKeyDown(KEY_RIGHT)) p.rotation += ROTATION_SPEED;

        else if (IsKeyDown(KEY_LEFT)) p.rotation -= ROTATION_SPEED;

        if (IsKeyDown(KEY_SPACE)) {
            Shoot();
        }

        if (IsKeyDown(KEY_DOWN)) gameStarted = false;
    }
}

inline Vector2 GetPlayerDir() {
    return (Vector2){ sinf(p.rotation * DEG2RAD), -cosf(p.rotation * DEG2RAD) };
}

void DrawBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (p.bullets[i].active) {
            DrawCircleV(p.bullets[i].position, 3, BLUE);
        }
    }
}

void UpdateBullet() {
    if (!gameStarted) return;

    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet *bullet = &p.bullets[i];

        if (bullet->active) {

            if (CheckCollisionCircles(bullet->position, 3, meteor.position, meteor.radius)) {
                meteor.position = (Vector2) {-5000, -5000};
                bullet->active = false;
            }
            // Atualiza a posição da bala com base na velocidade e direção
            bullet->position.x += BULLET_SPEED * bullet->direction.x;
            bullet->position.y += BULLET_SPEED * bullet->direction.y;

            // Verifica se a bala saiu da tela, se sim, desativa
            if (bullet->position.x > SCREEN_WIDTH || bullet->position.y > SCREEN_HEIGHT ||
                bullet->position.x < 0 || bullet->position.y < 0) {
                bullet->active = false;
            }
        }
    }
}

void InitMeteor() {
    meteor.position = (Vector2) {0, 0};
    meteor.radius = 50;
    meteor.direction = (Vector2) {(float)GetRandomValue(1, 5), (float)GetRandomValue(1, 5)};
}

void DrawMeteor() {
    DrawCircleV(meteor.position, meteor.radius, BROWN);
}

void UpdateMeteor() {
    if (!gameStarted) return;

    meteor.position.x += METEOR_SPEED * meteor.direction.x;
    meteor.position.y += METEOR_SPEED * meteor.direction.y;
}

void DrawGamePause() {
    if (!gameStarted) {
        DrawText("PRESS UP TO START", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 30, RED);
    }
}