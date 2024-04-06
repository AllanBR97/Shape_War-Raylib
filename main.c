#include "Game.h"

int main() {
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shape War");
    SetTargetFPS(60);

    Run();

    CloseWindow();
    return 0;
}