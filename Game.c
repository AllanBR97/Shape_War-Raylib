//
// Created by allan on 27/09/23.
//
#include "Game.h"

#define PLAYER_SPEED 3.0f
#define ROTATION_SPEED 3.0f
#define BULLET_SPEED 6.f

void InitPlayer(Player* player) {
    // Setup player
    player->position = (Vector2){ (float)screenWidth / 2.0f, (float)screenHeight / 2.0f };
    player->rotation = 0.0f;

    player->v1 = (Vector2){player->position.x, player->position.y - 15.0f};
    player->v2 = (Vector2){player->position.x - 20.0f, player->position.y + 15.0f};
    player->v3 = (Vector2){player->position.x + 20.0f, player->position.y + 15.0f};

    for (int i = 0; i < 3; ++i) {
        player->bullets[i].position = (Vector2){-100, -100};
    }
}

void RotatePlayer(Player* player) {
    Vector2 v1 = (Vector2){ player->position.x, player->position.y - 15.0f };
    Vector2 v2 = (Vector2){ player->position.x - 20.0f, player->position.y + 15.0f };
    Vector2 v3 = (Vector2){ player->position.x + 20.0f, player->position.y + 15.0f };

    // Rotate each vertex around the center
    v1 = (Vector2){
            player->position.x + (v1.x - player->position.x) * cosf(player->rotation * DEG2RAD) - (v1.y - player->position.y) * sinf(player->rotation * DEG2RAD),
            player->position.y + (v1.x - player->position.x) * sinf(player->rotation * DEG2RAD) + (v1.y - player->position.y) * cosf(player->rotation * DEG2RAD)
    };

    v2 = (Vector2){
            player->position.x + (v2.x - player->position.x) * cosf(player->rotation * DEG2RAD) - (v2.y - player->position.y) * sinf(player->rotation * DEG2RAD),
            player->position.y + (v2.x - player->position.x) * sinf(player->rotation * DEG2RAD) + (v2.y - player->position.y) * cosf(player->rotation * DEG2RAD)
    };

    v3 = (Vector2){
            player->position.x + (v3.x - player->position.x) * cosf(player->rotation * DEG2RAD) - (v3.y - player->position.y) * sinf(player->rotation * DEG2RAD),
            player->position.y + (v3.x - player->position.x) * sinf(player->rotation * DEG2RAD) + (v3.y - player->position.y) * cosf(player->rotation * DEG2RAD)
    };

    player->v1 = v1;
    player->v2 = v2;
    player->v3 = v3;
}

void Shoot(Player* player) {
    Vector2 direction = GetPlayerDir(player);
    player->bullets[0].active = true;
    player->bullets[0] = (Bullet){ player->v1,
                                   direction,
                                   true,
                                   player->rotation};
}

void DrawPlayer(const Player* player) {
    DrawTriangleLines(player->v1, player->v2, player->v3, RAYWHITE);
}

void WrapScreen(Player* player) {
    // Check if player is beyond the right edge
    if (player->position.x > (float)screenWidth) {
        player->position.x = 0;
    }
        // Check if player is beyond the left edge
    else if (player->position.x < 0) {
        player->position.x = (float)screenWidth;
    }

    // Check if player is beyond the bottom edge
    if (player->position.y > (float)screenHeight) {
        player->position.y = 0;
    }
        // Check if player is beyond the top edge
    else if (player->position.y < 0) {
        player->position.y = (float)screenHeight;
    }
}

void InputPlayer(Player* player) {
    Vector2 direction = GetPlayerDir(player);

    if (IsKeyDown(KEY_RIGHT)) {
        player->rotation += ROTATION_SPEED;
    }

    else if (IsKeyDown(KEY_LEFT)) {
        player->rotation -= ROTATION_SPEED;
    }

    if (IsKeyDown(KEY_SPACE)) {
        Shoot(player);
    }

    else if (IsKeyDown(KEY_UP)) {
        gameStarted = true;
    }

    if (gameStarted) {
        player->position.x += direction.x * PLAYER_SPEED;
        player->position.y += direction.y * PLAYER_SPEED;
    }

    RotatePlayer(player);
}

void DrawBullet(Player* player) {
    for (int i = 0; i < 3; i++) {
        if (player->bullets[i].active) {
            DrawCircle((int)player->bullets[i].position.x, (int)player->bullets[i].position.y, 3, BLUE);
        }
    }
}

inline Vector2 GetPlayerDir(const Player* player) {
    return (Vector2){ sinf(player->rotation * DEG2RAD), -cosf(player->rotation * DEG2RAD) };
}

void UpdateBullet(Player* player) {
    for (int i = 0; i < 3; i++) {
        Bullet *bullet = &player->bullets[i];

        if (bullet->active) {
            // Atualiza a posição da bala com base na velocidade e direção
            bullet->position.x += BULLET_SPEED * bullet->direction.x;
            bullet->position.y += BULLET_SPEED * bullet->direction.y;

            // Verifica se a bala saiu da tela, se sim, desativa
            if ((int)bullet->position.x > screenWidth || (int)bullet->position.y > screenHeight ||
                bullet->position.x < 0 || bullet->position.y < 0) {
                bullet->active = false;
            }
        }
    }
}