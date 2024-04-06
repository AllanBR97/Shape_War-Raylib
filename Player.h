//
// Created by allan on 06/04/24.
//
#include "Game.h"

#ifndef SHAPE_WAR_PLAYER_H
#define SHAPE_WAR_PLAYER_H

typedef struct {
    Vector2 v1, v2, v3, position;
    float rotation;
    Bullet bullets[MAX_BULLETS];
}Player;

extern Player p;

Vector2 GetPlayerDir();
void InitPlayer();
void DrawPlayer();
void ScreenWrap();
void InputPlayer();
void RotatePlayer();
void Shoot();

#endif //SHAPE_WAR_PLAYER_H
