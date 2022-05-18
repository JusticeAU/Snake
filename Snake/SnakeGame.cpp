#include "SnakeGame.h"
#include "snakeGrid.h"
#include "snakeInput.h"

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

void SnakeGame::Update()
{
    getInput(dir, dirPrevious);

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