//
// Created by allan on 06/04/24.
//
#include "Game.h"

#ifndef SHAPE_WAR_METEOR_H
#define SHAPE_WAR_METEOR_H

#define BIG_METEORS 5
#define METEOR_SPEED 2

typedef struct {
    Vector2 position, speed;
    float radius;
}Meteor;

extern Meteor meteor[BIG_METEORS];

void InitMeteor();
void DrawMeteor();
void UpdateMeteor();

#endif //SHAPE_WAR_METEOR_H
