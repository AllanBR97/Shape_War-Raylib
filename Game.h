//
// Created by allan on 27/09/23.
//
#include "raylib.h"
#include <math.h>

#ifndef SHAPE_WAR_GAME_H
#define SHAPE_WAR_GAME_H

#define PLAYER_SPEED 3.0f
#define ROTATION_SPEED 3.0f

#define BULLET_SPEED 9.0f
#define MAX_BULLETS 3
#define BULLET_RADIUS 3

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800

typedef struct {
    Vector2 position, direction;
    bool active;
}Bullet;

extern int indexBullet;

extern bool gameStarted;

void SetupGame();
void DrawGamePause();

void UpdateBullet();
void DrawBullet();
#endif //SHAPE_WAR_GAME_H
