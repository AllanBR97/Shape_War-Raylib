//
// Created by allan on 27/09/23.
//
#include <math.h>
//#include <stdio.h>
#include "Game.h"

#define PLAYER_SPEED 3.0f
#define ROTATION_SPEED 5.0f

void InitPlayer(Player* player) {
    // Setup player
    player->position = (Vector2){ (float)screenWidth / 2.0f, (float)screenHeight / 2.0f };
    player->rotation = 0.0f;

    player->v1 = (Vector2){player->position.x, player->position.y - 15.0f};
    player->v2 = (Vector2){player->position.x - 20.0f, player->position.y + 15.0f};
    player->v3 = (Vector2){player->position.x + 20.0f, player->position.y + 15.0f};
}

void MovePlayer(Player* player) {
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

void Shoot() {}

void DrawPlayer(Player* player) {
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
    Vector2 direction = { sinf(player->rotation * DEG2RAD), -cosf(player->rotation * DEG2RAD) };

    if (IsKeyDown(KEY_RIGHT)) {
        player->rotation += ROTATION_SPEED;
    }

    if (IsKeyDown(KEY_LEFT)) {
        player->rotation -= ROTATION_SPEED;
    }

    if (IsKeyDown(KEY_SPACE)) {
        // Shoot
    }

    if (IsKeyDown(KEY_UP)) {
        gameStarted = true;
    }

    if (gameStarted) {
        player->position.x += direction.x * PLAYER_SPEED;
        player->position.y += direction.y * PLAYER_SPEED;
    }

    MovePlayer(player);
    WrapScreen(player);
}

void DrawBullet(Player* player) {
    Vector2 pos = player->v1;
    Vector2 direction = { sinf(player->rotation * DEG2RAD), -cosf(player->rotation * DEG2RAD) };
    Vector2 endPos = { pos.x + direction.x * 10, pos.y + direction.y * 10 };
    DrawLineEx(pos, endPos, 1, RAYWHITE);
}
