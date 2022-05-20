#include "SnakeGame.h"
#include <iostream>


SnakeGame::SnakeGame()
{
    grid = new int[gridRows * gridColumns]();

    // column/x = index % gridColumns
    // row/y = index / gridColumns
    // x: 5, y:5 = index of: 5 * gridColumns + 5, or (y * gridColums) + x
    grid[(5 * gridColumns) + 5] = 1;

    dir = up;

    // Spawn initial food.
    randomize();
    spawnFood(grid, gridColumns * gridRows);
}
SnakeGame::~SnakeGame()
{
    delete grid;
}

Status SnakeGame::Update(Status status)
{
    getInput(dir, dirPrevious);
    if (IsKeyPressed(KEY_P))
    {
        std::cout << "Paused";
        status.paused = true;
    }
        

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
        if (playerPosIndex == -1)
        {
            gameover = true;
        }

        if (!gameover)
        {
            // Test for consuming food at index
            if (grid[playerPosIndex] == -1)
            {
                // Spawn a new food, increase our length, and increase the life of all snake occupying cells.
                spawnFood(grid, gridColumns * gridRows);
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
                dirPrevious = dir;
            }
        }
    }
    if (gameover) status.paused = true;
    return status;
}
void SnakeGame::Draw()
{
    // Draw Grid using 2D coodinates.
    for (int y = 0; y < gridRows; y++)
    {
        for (int x = 0; x < gridColumns; x++)
        {
            int i = gridIndex(x, y, gridColumns, gridRows);
            // Test for empty cell
            if (grid[i] == 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, LIGHTGRAY);
            // test for snake body
            if (grid[i] > 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, DARKGRAY);
            // test for food
            if (grid[i] < 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, GREEN);
            // test for crash
            if (grid[i] == -2) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, RED);
        }
    }
    if (gameover)
    {
        DrawRectangle(gridXOrigin + (playerX * gridCellSize), gridYOrigin + (playerY * gridCellSize), gridCellSize, gridCellSize, RED);
    }
}
// Gets keyboard input, tests our previous direction to ensure our new direction is valid, and updates the direction variable
void SnakeGame::getInput(int& dir, const int dirPrevious)
{

    if (IsKeyPressed(KEY_UP))
    {
        if (dirPrevious != down)
            dir = up;
    }
    if (IsKeyPressed(KEY_DOWN))
    {
        if (dirPrevious != up)
            dir = down;
    }
    if (IsKeyPressed(KEY_LEFT))
    {
        if (dirPrevious != right)
            dir = left;
    }
    if (IsKeyPressed(KEY_RIGHT))
    {
        if (dirPrevious != left)
            dir = right;
    }
}
// Calculates an index for a 1D array based on 2D coordinates.
// If the index is outout bounds, it will return -1.
int SnakeGame::gridIndex(const int columnX, const int rowY, const int gridColumns, const int gridRows)
{
    // test for valid x/y
    if (columnX < 0 || columnX >= gridColumns || rowY < 0 || rowY >= gridRows) return -1;
    int index = (rowY * gridColumns) + columnX;
    return index;
}

// Sets the random seed for the game based on time to make every game different.
void SnakeGame::randomize()
{
    srand(time(nullptr));
}

// Selects a random location, checks if its free and spawns a food object here.
void SnakeGame::spawnFood(int grid[], const int gridSize)
{
    // Spawn a random food.
    int food = rand() % (gridSize);

    while (grid[food] != 0)
    {
        food = rand() % (gridSize);
    }
    grid[food] = -1;
}