//
// Created by allan on 06/04/24.
//
#include "Game.h"

#ifndef SHAPE_WAR_BULLET_H
#define SHAPE_WAR_BULLET_H

#define BULLET_SPEED 10.f
#define MAX_BULLETS 3
#define BULLET_RADIUS 3

typedef struct {
    Vector2 position, direction;
    bool active;
}Bullet;

extern int indexBullet;

void UpdateBullet();
void DrawBullet();
#endif //SHAPE_WAR_BULLET_H
