//
// Created by allan on 06/04/24.
//

#include "Bullet.h"
#include "Player.h"
#include "Meteor.h"

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
            // Check collision
            for (int j = 0; j < BIG_METEORS; ++j) {
                if (CheckCollisionMeteor(bullet, &meteor[j]) && meteor[j].active) {
                    SpawnMeteor(j);
                    meteor[j].active = false;
                    bullet->active = false;
                }
            }
            // Update bullets
            bullet->position.x += BULLET_SPEED * bullet->direction.x;
            bullet->position.y += BULLET_SPEED * bullet->direction.y;

            // Check if bullets have left the screen
            if (bullet->position.x > SCREEN_WIDTH || bullet->position.y > SCREEN_HEIGHT ||
                bullet->position.x < 0 || bullet->position.y < 0) {
                bullet->active = false;
            }
        }
    }
}

bool CheckCollisionMeteor(Bullet* bullet, Meteor* m) {
    if (CheckCollisionCircles(bullet->position, BULLET_RADIUS, m->position, m->radius)) {
        return true;
    }
    return false;
}