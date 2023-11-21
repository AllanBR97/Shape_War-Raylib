//
// Created by allan on 27/09/23.
//
#include <math.h>
#include <stdio.h>
#include "Player.h"

bool keepDirection = false;

void InitPlayer(Player* player) {
    // Setup player
    player->position = (Vector2){ (float)screenWidth / 2.0f, (float)screenHeight / 2.0f };
    player->rotation = 0.0f;
    player->speed = 3.0f; // Movement speed
    player->rotationSpeed = 2.0f; // Rotation speed in degrees

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

void InputPlayer(Player* player) {
    Vector2 direction = { sinf(player->rotation * DEG2RAD), -cosf(player->rotation * DEG2RAD) };

    if (IsKeyDown(KEY_RIGHT)) {
        player->rotation += player->rotationSpeed;
        MovePlayer(player);
    }

    if (IsKeyDown(KEY_LEFT)) {
        player->rotation -= player->rotationSpeed;
        MovePlayer(player);
    }

    if (IsKeyDown(KEY_SPACE)) {
        // Shoot
    }

    if (IsKeyDown(KEY_UP)) {
        keepDirection = true;

        if (player->position.x > (float)screenWidth || player->position.y > (float)screenHeight) {
            puts("WRAP!!!");
        }
    }

    if (keepDirection) {
        player->position.x += direction.x * player->speed;
        player->position.y += direction.y * player->speed;
        MovePlayer(player);
    }
}
