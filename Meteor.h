//
// Created by allan on 06/04/24.
//
#include "Game.h"

#ifndef SHAPE_WAR_METEOR_H
#define SHAPE_WAR_METEOR_H

#define BIG_METEORS 5
#define MEDIUM_METEORS 7
#define SMALL_METEORS 10

#define METEOR_SPEED 2

typedef struct {
    Vector2 position, speed;
    float radius;
    bool active;
}Meteor;

extern Meteor meteor[BIG_METEORS];
extern Meteor meteorMedium[MEDIUM_METEORS];
extern Meteor meteorSmall[SMALL_METEORS];

void SpawnMeteor(int);
void InitMeteors();
void DrawMeteors();
void UpdateMeteors();

#endif //SHAPE_WAR_METEOR_H
