#include "enums.h"
#include "raylib.h"
#include "SnakeGame.h"
#include "SnakeMenu.h"
#include "status.h"

//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_ICONS

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;
    
    Status status = {};

    SnakeGame* sg = new SnakeGame(screenWidth, screenHeight, 10, 14, 64, status);
    SnakeMenu* sm = new SnakeMenu();

    InitWindow(screenWidth, screenHeight, "Snake");
    SetExitKey(NULL);

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!status.quitRequested)
    {
        //// Update
        ////----------------------------------------------------------------------------------
        if (status.restartRequested)
        {
            delete sg;
            sg = new SnakeGame(screenWidth, screenHeight, 10, 14, 64, status);
            status.restartRequested = false;
        }

        if(!status.paused)
            sg->Update(status);
        else
            sm->Update(status);

        //// Draw
        ////----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        sg->Draw(status);
        if(status.paused)
            sm->Draw(status);
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}