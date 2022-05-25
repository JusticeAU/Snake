/*******************************************************************************************
*
*   raylib [core] example - Basic window
*
*   Welcome to raylib!
*
*   To test examples, just press F6 and execute raylib_compile_execute script
*   Note that compiled executable is placed in the same folder as .c file
*
*   You can find all basic examples on C:\raylib\raylib\examples folder or
*   raylib official webpage: www.raylib.com
*
*   Enjoy using raylib. :)
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

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

    SnakeGame* sg = new SnakeGame(screenWidth, screenHeight, 10, 14, 64);
    SnakeMenu* sm = new SnakeMenu();

    InitWindow(screenWidth, screenHeight, "Snake");

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
            sg = new SnakeGame(screenWidth, screenHeight, 10, 14, 64);
            status.restartRequested = false;
        }

        if(!status.paused)
            status = sg->Update(status);
        else
            status = sm->Update(status);

        //// Draw
        ////----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(RAYWHITE);
        sg->Draw(status);
        if(status.paused)
            sm->Draw();
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}