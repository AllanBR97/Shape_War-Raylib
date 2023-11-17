//
// Created by allan on 27/09/23.
//
#include "raylib.h"

#ifndef SHAPE_WAR_PLAYER_H
#define SHAPE_WAR_PLAYER_H

struct Player {
    Vector2 v1, v2, v3, position;
    float rotation, speed, rotationSpeed;
};

typedef struct Player Player;
extern const int screenWidth;
extern const int screenHeight;

void InitPlayer(Player *);
void DrawPlayer(Player *);
void InputPlayer(Player *);
void MovePlayer(Player *);
void Shoot(Player *);

#endif //SHAPE_WAR_PLAYER_H
