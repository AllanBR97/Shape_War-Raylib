//
// Created by allan on 27/09/23.
//
#include "raylib.h"

#ifndef SHAPE_WAR_GAME_H
#define SHAPE_WAR_GAME_H

typedef struct {
    Vector2 v1, v2, v3, position;
    float rotation;
}Player;

typedef struct {
    Vector2 position, direction;
    float speed;
}Bullet;

extern bool gameStarted;
extern const int screenWidth;
extern const int screenHeight;

void InitPlayer(Player *);
void DrawPlayer(Player *);
void WrapScreen(Player *);
void InputPlayer(Player *);
void MovePlayer(Player *);
void Shoot();

void DrawBullet(Player *);
#endif //SHAPE_WAR_PLAYER_H
