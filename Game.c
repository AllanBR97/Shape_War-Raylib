//
// Created by allan on 27/09/23.
//
#include "Game.h"

int indexBullet = 0;

bool gameStarted;
Player p;
Meteor meteor[BIG_METEORS];

void SetupGame() {
    gameStarted = true;
    InitPlayer();
    InitMeteor();
}

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

/*bool CheckCollisionMeteor() {
    Vector2 offset1 = {p.v1.x - meteor.radius, p.v1.y - meteor.radius};
    Vector2 offset2 = {p.v2.x - meteor.radius, p.v2.y - meteor.radius};
    Vector2 offset3 = {p.v3.x - meteor.radius, p.v3.y - meteor.radius};

    if (sqrtf(offset1.x * offset1.x + offset1.y * offset1.y) <= meteor.radius &&
            sqrtf(offset2.x * offset2.x + offset2.y * offset2.y) <= meteor.radius &&
            sqrtf(offset3.x * offset3.x + offset3.y * offset3.y) <= meteor.radius) return true;
    return false;
}*/

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

void DrawBullet() {
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (p.bullets[i].active) {
            DrawCircleV(p.bullets[i].position, BULLET_RADIUS, BLUE);
        }
    }
}

void UpdateBullet() {
    if (!gameStarted) return;

    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet *bullet = &p.bullets[i];

        if (bullet->active) {
            for (int j = 0; j < BIG_METEORS; ++j) {
                if (CheckCollisionCircles(bullet->position, BULLET_RADIUS, meteor[j].position, meteor[j].radius)) {
                    meteor[j].position = (Vector2) {-100, -100};
                    bullet->active = false;
                }
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
    for (int i = 0; i < BIG_METEORS; ++i) {
        meteor[i].position = (Vector2) {0, 0};
        meteor[i].radius = 50;
        meteor[i].direction = (Vector2) {(float)GetRandomValue(1, 5), (float)GetRandomValue(1, 5)};
    }
}

void DrawMeteor() {
    for (int i = 0; i < BIG_METEORS; ++i) {
        DrawCircleV(meteor[i].position, meteor[i].radius, BROWN);
    }
}

void UpdateMeteor() {
    if (!gameStarted) return;

    for (int i = 0; i < BIG_METEORS; ++i) {
        meteor[i].position.x += METEOR_SPEED * meteor[i].direction.x;
        meteor[i].position.y += METEOR_SPEED * meteor[i].direction.y;
    }
}

void DrawGamePause() {
    if (!gameStarted) {
        DrawText("PRESS UP TO START", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 30, RED);
    }
}