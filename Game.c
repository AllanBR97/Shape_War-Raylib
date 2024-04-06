//
// Created by allan on 27/09/23.
//
#include "Game.h"
#include "Meteor.h"
#include "Player.h"

int indexBullet;
bool gameStarted;
Player p;

void SetupGame() {
    gameStarted = true;
    InitPlayer();
    InitMeteor();
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

void DrawGamePause() {
    if (!gameStarted) {
        DrawText("PRESS UP TO START", SCREEN_WIDTH / 2 - 150, SCREEN_HEIGHT / 2, 30, RED);
    }
}