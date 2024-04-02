//
// Created by allan on 27/09/23.
//
#include "raylib.h"
#include <math.h>

#ifndef SHAPE_WAR_GAME_H
#define SHAPE_WAR_GAME_H

#define PLAYER_SPEED 3.0f
#define ROTATION_SPEED 3.0f
#define BULLET_SPEED 9.f
#define MAX_BULLETS 3
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
    Bullet bullets[3];
}Player;

extern bool gameStarted;

void DrawGamePause();

Vector2 GetPlayerDir(const Player *);
void InitPlayer(Player *);
void DrawPlayer(const Player *);
void WrapScreen(Player *, Meteor *);
void InputPlayer(Player *);
void RotatePlayer(Player *);
void Shoot(Player *);

void UpdateBullet(Player *);
void DrawBullet(Player *);

void InitMeteor(Meteor *);
void DrawMeteor(const Meteor *);
void UpdateMeteor(Meteor *);
#endif //SHAPE_WAR_GAME_H
