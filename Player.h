//
// Created by allan on 06/04/24.
//
#include "Game.h"
#include "Bullet.h"

#ifndef SHAPE_WAR_PLAYER_H
#define SHAPE_WAR_PLAYER_H

#define PLAYER_SPEED 3.0f
#define ROTATION_SPEED 3.0f

typedef struct {
    Vector2 v1, v2, v3, position;
    float rotation;
    Bullet bullets[MAX_BULLETS];
}Player;

extern Player p;

Vector2 GetPlayerDir();
void InitPlayer();
void DrawPlayer();
void UpdatePlayer();

#endif //SHAPE_WAR_PLAYER_H
