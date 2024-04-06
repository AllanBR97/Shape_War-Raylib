//
// Created by allan on 06/04/24.
//
#include "Meteor.h"

Meteor meteor[BIG_METEORS];

void InitMeteor() {
    for (int i = 0; i < BIG_METEORS; ++i) {
        meteor[i].position = (Vector2) {0, 0};
        meteor[i].radius = 50;
        meteor[i].direction = (Vector2) {(float)GetRandomValue(1, 5), (float)GetRandomValue(1, 5)};
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
        meteor[i].position.x += METEOR_SPEED * meteor[i].direction.x;
        meteor[i].position.y += METEOR_SPEED * meteor[i].direction.y;
    }
}