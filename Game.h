//
// Created by allan on 27/09/23.
//
#include "raylib.h"
#include <math.h>

#ifndef SHAPE_WAR_GAME_H
#define SHAPE_WAR_GAME_H

#define SCREEN_HEIGHT 800
#define SCREEN_WIDTH 800

extern bool gameStarted;

void Run();
void Update();
void Draw();
void SetupGame();
void DrawGamePause();

#endif //SHAPE_WAR_GAME_H
