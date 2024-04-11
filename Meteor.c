//
// Created by allan on 06/04/24.
//
#include "Meteor.h"

Meteor meteor[BIG_METEORS];
Meteor meteorMedium[MEDIUM_METEORS];
Meteor meteorSmall[SMALL_METEORS];

void InitMeteors() {
    for (int i = 0; i < BIG_METEORS; ++i) {
        int rndX = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
        int rndY = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);

        while (rndX == 0 && rndY == 0) {
            rndX = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
            rndY = GetRandomValue(-METEOR_SPEED, METEOR_SPEED);
        }

        meteor[i].position = (Vector2) {rndX, rndY};
        meteor[i].active = true;
        meteor[i].radius = 50;
        meteor[i].speed = (Vector2) {rndX, rndY};
    }

    for (int i = 0; i < MEDIUM_METEORS; ++i) {
        meteorMedium[i].radius = 25;
        meteorMedium[i].active = false;
        meteorMedium[i].speed = (Vector2) {};
    }

    for (int i = 0; i < SMALL_METEORS; ++i) {
        meteorSmall[i].radius = 10;
        meteorSmall[i].active = false;
        meteorSmall[i].speed = (Vector2) {};
    }
}

void SpawnMeteor(int id) {
    meteorMedium[id].active = true;
    meteorMedium[id].position = meteor[id].position;

    /*meteorMedium[id + 1].active = true;
    meteorMedium[id + 1].position = meteor[id].position;
    meteorMedium[id + 1].position.x = meteor[id].position.x / 2;

    meteorMedium[id + 2].active = true;
    meteorMedium[id + 2].position = meteor[id].position;
    meteorMedium[id + 2].position.y = meteor[id].position.y / 2;*/
}

void DrawMeteors() {
    for (int i = 0; i < BIG_METEORS; ++i) {
        if (meteor[i].active) {
            DrawCircleV(meteor[i].position, meteor[i].radius, BROWN);
        }
    }

    for (int i = 0; i < MEDIUM_METEORS; ++i) {
        if (meteorMedium[i].active) {
            DrawCircleV(meteorMedium[i].position, meteorMedium[i].radius, BROWN);
        }
    }

    for (int i = 0; i < SMALL_METEORS; ++i) {
        if (meteorSmall[i].active) {
            DrawCircleV(meteorSmall[i].position, meteorSmall[i].radius, BROWN);
        }
    }
}

void UpdateMeteors() {
    if (!gameStarted) return;

    for (int i = 0; i < BIG_METEORS; ++i) {
        meteor[i].position.x += METEOR_SPEED * meteor[i].speed.x;
        meteor[i].position.y += METEOR_SPEED * meteor[i].speed.y;
    }
}