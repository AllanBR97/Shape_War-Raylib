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
        if (CheckCollision()) {
            p.position = (Vector2) {400, 400};
        }
        p.position.x += GetPlayerDir().x * PLAYER_SPEED;
        p.position.y += GetPlayerDir().y * PLAYER_SPEED;
    }
}

void DrawPlayer() {
    DrawTriangleLines(p.v1, p.v2, p.v3, YELLOW);
}

// Check if a point is in a circle
bool PointInsideCircle(Vector2 vector2, float cx, float cy, float radius) {
    float dx = vector2.x - cx;
    float dy = vector2.y - cy;
    return (dx*dx + dy*dy) <= (radius * radius);
}

bool CheckCollision() {
    for (int i = 0; i < BIG_METEORS; ++i) {
        float radius = meteor[i].radius;
        float cx = meteor[i].position.x;
        float cy = meteor[i].position.y;

        // Check if a vertex is in a radius
        if (PointInsideCircle(p.v1, cx, cy, radius) ||
            PointInsideCircle(p.v2, cx, cy, radius) ||
            PointInsideCircle(p.v3, cx, cy, radius)) {
            return true;
        }
    }
    return false;
}

inline Vector2 GetPlayerDir() {
    return (Vector2){ sinf(p.rotation * DEG2RAD), -cosf(p.rotation * DEG2RAD) };
}