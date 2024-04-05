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

#define BIG_METEORS 5
#define METEOR_SPEED 0.5f

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800

typedef struct {
    Vector2 position, direction;
    float radius;
}Meteor;

typedef struct {
    Vector2 position, direction;
    bool active;
}Bullet;

typedef struct {
    Vector2 v1, v2, v3, position;
    float rotation;
    Bullet bullets[MAX_BULLETS];
}Player;

void SetupGame();
void DrawGamePause();

//bool CheckCollisionMeteor();
Vector2 GetPlayerDir();
void InitPlayer();
void DrawPlayer();
void ScreenWrap();
void InputPlayer();
void RotatePlayer();
void Shoot();

void UpdateBullet();
void DrawBullet();

void InitMeteor();
void DrawMeteor();
void UpdateMeteor();
#endif //SHAPE_WAR_GAME_H
