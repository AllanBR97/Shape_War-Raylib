//
// Created by allan on 27/09/23.
//
#include "Game.h"

void InitPlayer(Player* player) {
    // Setup player
    player->position = (Vector2){ (float)SCREEN_WIDTH / 2.0f, (float)SCREEN_HEIGHT / 2.0f };
    player->rotation = 0.0f;

    player->v1 = (Vector2){player->position.x, player->position.y - 20.0f};
    player->v2 = (Vector2){player->position.x - 20.0f, player->position.y + 20.0f};
    player->v3 = (Vector2){player->position.x + 20.0f, player->position.y + 20.0f};

    for (int i = 0; i < MAX_BULLETS; ++i) {
        player->bullets[i].active = false;
        player->bullets[i].position = (Vector2){-100, -100};
    }
}

void RotatePlayer(Player* player) {
    Vector2 v1 = (Vector2){ player->position.x, player->position.y - 20.0f };
    Vector2 v2 = (Vector2){ player->position.x - 20.0f, player->position.y + 20.0f };
    Vector2 v3 = (Vector2){ player->position.x + 20.0f, player->position.y + 20.0f };

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
    for (int i = 0; i < MAX_BULLETS; ++i) {
        player->bullets[i] = (Bullet){ player->v1,
                                       direction,
                                       true};
    }
}

void DrawPlayer(const Player* player) {
    DrawTriangleLines(player->v1, player->v2, player->v3, YELLOW);
}

void WrapScreen(Player* player, Meteor* meteor) {
    // Verifica o tamanho do jogador
    float playerHalfWidth = 20;
    float playerHalfHeight = 20;

    // Verifica o tamanho do meteoro
    float meteorHalfWidth = meteor->radius;
    float meteorHalfHeight = meteor->radius;

    // Check if player is beyond the right edge
    if (player->position.x > SCREEN_WIDTH + playerHalfWidth) {
        player->position.x = -playerHalfWidth;
    }
        // Check if player is beyond the left edge
    else if (player->position.x < -playerHalfWidth) {
        player->position.x = SCREEN_WIDTH + playerHalfWidth;
    }

    // Check if player is beyond the bottom edge
    if (player->position.y > SCREEN_HEIGHT + playerHalfHeight) {
        player->position.y = -playerHalfHeight;
    }
        // Check if player is beyond the top edge
    else if (player->position.y < -playerHalfHeight) {
        player->position.y = SCREEN_HEIGHT + playerHalfHeight;
    }

    // Check if meteor is beyond the right edge
    if (meteor->position.x > SCREEN_WIDTH + meteorHalfWidth) {
        meteor->position.x = -meteorHalfWidth;
    }
        // Check if meteor is beyond the left edge
    else if (meteor->position.x < -meteorHalfWidth) {
        meteor->position.x = SCREEN_WIDTH + meteorHalfWidth;
    }

    // Check if meteor is beyond the bottom edge
    if (meteor->position.y > SCREEN_HEIGHT + meteorHalfHeight) {
        meteor->position.y = -meteorHalfHeight;
    }
        // Check if meteor is beyond the top edge
    else if (meteor->position.y < -meteorHalfHeight) {
        meteor->position.y = SCREEN_HEIGHT + meteorHalfHeight;
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
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (player->bullets[i].active) {
            DrawCircleV((Vector2) {player->bullets[i].position.x, player->bullets[i].position.y}, 3, BLUE);
        }
    }
}

inline Vector2 GetPlayerDir(const Player* player) {
    return (Vector2){ sinf(player->rotation * DEG2RAD), -cosf(player->rotation * DEG2RAD) };
}

void UpdateBullet(Player* player) {
    for (int i = 0; i < MAX_BULLETS; i++) {
        Bullet *bullet = &player->bullets[i];

        if (bullet->active) {
            // Atualiza a posição da bala com base na velocidade e direção
            bullet->position.x += BULLET_SPEED * bullet->direction.x;
            bullet->position.y += BULLET_SPEED * bullet->direction.y;

            // Verifica se a bala saiu da tela, se sim, desativa
            if ((int)bullet->position.x > SCREEN_WIDTH || (int)bullet->position.y > SCREEN_HEIGHT ||
                bullet->position.x < 0 || bullet->position.y < 0) {
                bullet->active = false;
            }
        }
    }
}

void InitMeteor(Meteor* meteor) {
    meteor->position = (Vector2) {0, 0};
    meteor->radius = 50;
    meteor->direction = (Vector2) {(float)GetRandomValue(1, 5), (float)GetRandomValue(1, 5)};
}

void DrawMeteor(const Meteor* meteor) {
    DrawCircle((int)meteor->position.x, (int)meteor->position.y, meteor->radius, BROWN);
}

void UpdateMeteor(Meteor* meteor) {
    if (gameStarted) {
        meteor->position.x += METEOR_SPEED * meteor->direction.x;
        meteor->position.y += METEOR_SPEED * meteor->direction.y;
    }
}
