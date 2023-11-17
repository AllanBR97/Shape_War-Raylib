//
// Created by allan on 27/09/23.
//

#include "Player.h"

void InitPlayer(Player* player) {
    player->v1 = (Vector2){800 / 2.0f, 600 / 2.0f - 15.0f};
    player->v2 = (Vector2){800 / 2.0f - 20.0f, 600 / 2.0f + 20.0f};
    player->v3 = (Vector2){800 / 2.0f + 20.0f, 600 / 2.0f + 20.0f};
}


void RotatePlayer(Player* player) {}
void Shoot(Player* player) {}

void DrawPlayer(Player* player) {
    DrawTriangleLines(player->v1, player->v2, player->v3, RAYWHITE);
}

void InputPlayer(Player* player) {
    if (IsKeyDown(KEY_RIGHT)) {
        player->v1.x += 5.0f;
        player->v2.x += 5.0f;
        player->v3.x += 5.0f;
    }

    if (IsKeyDown(KEY_LEFT)) {
        player->v1.x -= 5.0f;
        player->v2.x -= 5.0f;
        player->v3.x -= 5.0f;
    }

    if (IsKeyDown(KEY_SPACE)) {
        // Shoot
    }
}
