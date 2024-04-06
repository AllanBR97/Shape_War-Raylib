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

void UpdatePlayer() {
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

    if (gameStarted) {
        p.position.x += GetPlayerDir().x * PLAYER_SPEED;
        p.position.y += GetPlayerDir().y * PLAYER_SPEED;
    }
}

void DrawPlayer() {
    DrawTriangleLines(p.v1, p.v2, p.v3, YELLOW);
}

inline Vector2 GetPlayerDir() {
    return (Vector2){ sinf(p.rotation * DEG2RAD), -cosf(p.rotation * DEG2RAD) };
}