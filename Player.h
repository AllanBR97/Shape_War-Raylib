//
// Created by allan on 27/09/23.
//
#include "raylib.h"

#ifndef SHAPE_WAR_PLAYER_H
#define SHAPE_WAR_PLAYER_H

struct Player {
    Vector2 v1, v2, v3;
    void (*action) (struct Player *); // Responds to input from user (shooting function, rotate function etc.)
};

typedef struct Player Player;

void InitPlayer(Player *);
void DrawPlayer(Player *);
void InputPlayer(Player *);
void RotatePlayer(Player *);
void Shoot(Player *);

#endif //SHAPE_WAR_PLAYER_H
