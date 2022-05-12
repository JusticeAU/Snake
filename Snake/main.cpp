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

#include "raylib.h"
#include "snakeGrid.h"

//#define RAYGUI_IMPLEMENTATION
//#define RAYGUI_SUPPORT_ICONS

int main(int argc, char* argv[])
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int screenWidth = 1280;
    int screenHeight = 720;

    // grid configuration
    const int gridRows = 10;
    const int gridColumns = 14;
    const int gridCellSize = 64;

    // Set up rendering offset for grid.
    int gridXOrigin = (screenWidth / 2) - (gridColumns / 2) * gridCellSize;
    int gridYOrigin = (screenHeight / 2) - (gridRows / 2) * gridCellSize;

    // Create the 1D grid
    int grid[gridRows * gridColumns] = { 0 };

    // column/x = index % gridColumns
    // row/y = index / gridColumns
    // x: 5, y:5 = index of: 5 * gridColumns + 5, or (y * gridColums) + x
    grid[(5 * gridColumns) + 5] = 1;

    // Input direction
    enum direction {
        up,
        down,
        left,
        right
    };

    // Store player 'head' position
    int playerX = 5;
    int playerY = 5;
    int dir = up;

    int frames = 0;
    int framesPerGameStep = 15;
    int snakeLength = 1;

    bool gameover = false;
    
    // Spawn initial food.
    randomize();
    spawnFood(grid, gridColumns* gridRows);

    InitWindow(screenWidth, screenHeight, "Snake");

    SetTargetFPS(60);
    //--------------------------------------------------------------------------------------
    
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        
        // Get Input
        if (IsKeyPressed(KEY_UP)) dir = up;
        if (IsKeyPressed(KEY_DOWN)) dir = down;
        if (IsKeyPressed(KEY_LEFT)) dir = left;
        if (IsKeyPressed(KEY_RIGHT)) dir = right;

        // Track our frames.
        if (!gameover) frames++;

        // Test enough frames have passed and if so, advance the game state.
        if (frames >= framesPerGameStep)
        {
            frames = 0; // Reset

            // update player position based on direction
            switch (dir)
            {
            case up:
                playerY -= 1;
                break;
            case down:
                playerY += 1;
                break;
            case left:
                playerX -= 1;
                break;
            case right:
                playerX += 1;
                break;
            }
            
            // Get our index on the grid for checks.
            int playerPosIndex = gridIndex(playerX, playerY, gridColumns, gridRows);

            // Test for consuming food at index
            if (grid[playerPosIndex] == -1)
            {
                // Spawn a new food, increase our length, and increase the life of all snake occupying cells.
                spawnFood(grid, gridColumns* gridRows);
                snakeLength++;
                for (int i = 0; i < gridRows * gridColumns; i++)
                {
                    if (grid[i] > 0)  grid[i]++;
                }
            }
            else
            {
                // Otherwise, decrease cell lifetime on all snake occupying cells.
                for (int i = 0; i < gridRows * gridColumns; i++)
                {
                    if (grid[i] > 0)  grid[i]--;
                }
            }

            // Test for collision with ourself.
            if (grid[playerPosIndex] > 0)
            {
                grid[playerPosIndex] = -2;
                gameover = true;
            }
            else
            {
                // Place our new head.
                grid[playerPosIndex] = snakeLength;
            }
        }


        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw Grid using 2D coodinates.
        for (int y = 0; y < gridRows; y++)
        {
            for (int x = 0; x < gridColumns; x++)
            {
                int i = gridIndex(x, y, gridColumns, gridRows);
                // Test for empty cell
                if (grid[i] == 0) DrawRectangle(gridXOrigin + (x * gridCellSize),gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, LIGHTGRAY);
                // test for snake body
                if (grid[i] > 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, DARKGRAY);
                // test for food
                if (grid[i] < 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, GREEN);
                // test for crash
                if (grid[i] == -2) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, RED);
            }
        }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------   
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}