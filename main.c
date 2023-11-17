#include "raylib.h"
#include "Player.h"
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------

const int screenWidth = 800;
const int screenHeight = 600;

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    Player player;

    InitWindow(screenWidth, screenHeight, "Shape War");
    InitPlayer(&player);

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        InputPlayer(&player);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(BLACK);

        DrawPlayer(&player);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}