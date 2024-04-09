//
// Created by allan on 06/04/24.
//
#include "Meteor.h"

Meteor meteor[BIG_METEORS];

void InitMeteor() {
    for (int i = 0; i < BIG_METEORS; ++i) {
        int spdX = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
        int spdY = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);

        while (spdX == 0 && spdY == 0) {
            spdX = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
            spdY = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
        }

        meteor[i].position = (Vector2) {0, 0};
        meteor[i].radius = 50;
        meteor[i].speed = (Vector2) {spdX, spdY};
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
        meteor[i].position.x += METEOR_SPEED * meteor[i].speed.x;
        meteor[i].position.y += METEOR_SPEED * meteor[i].speed.y;
    }
}