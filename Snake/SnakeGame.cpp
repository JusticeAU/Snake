#include "SnakeGame.h"
#include <string>

SnakeGame::SnakeGame(const int screenWidth, const int screenHeight, const int gridRows, const int gridColumns, const int gridCellSize, Status& status)
{
    this->gridColumns = gridColumns;
    this->gridRows = gridRows;
    this->gridCellSize = gridCellSize;

    // Calculate the origin we should start drawing the grid from to centre it.
    gridXOrigin = (screenWidth / 2) - (gridColumns / 2) * gridCellSize;
    gridYOrigin = (screenHeight / 2) - (gridRows / 2) * gridCellSize;

    // Create new game world
    grid = new int[gridRows * gridColumns]();


    // Spawn the player.
    // column/x = index % gridColumns
    // row/y = index / gridColumns
    // x: 5, y:5 = index of: 5 * gridColumns + 5, or (y * gridColums) + x
    grid[(playerY * gridColumns) + playerX] = 1;

    // Set default travel direction.
    dir = right;

    // Spawn initial food.
    randomize();
    spawnFood(grid, gridColumns * gridRows, status);
}
SnakeGame::~SnakeGame()
{
    delete grid;
}

void SnakeGame::Update(Status& status)
{
    getInput(dir, dirPrevious);
    
    if (IsKeyPressed(KEY_ESCAPE))
        status.paused = true;
        
    // Track our frames.
    if (!status.gameover) frames++;

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
            status.gameover = true;
        }

        if (!status.gameover)
        {
            // Test for consuming food at index
            if (grid[playerPosIndex] == -1)
            {
                // Spawn a new food, increase our length.
                spawnFood(grid, gridColumns * gridRows, status);
                snakeLength++;
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
                status.gameover = true;
            }
            else
            {
                // Place our new head.
                grid[playerPosIndex] = snakeLength;
                dirPrevious = dir;
            }
        }
    }
    if (status.gameover) status.paused = true;
    return ;
}
void SnakeGame::Draw(const Status& status)
{
    // Draw Grid using 2D coodinates.
    for (int y = 0; y < gridRows; y++)
    {
        for (int x = 0; x < gridColumns; x++)
        {
            int i = gridIndex(x, y, gridColumns, gridRows);
            // Test for empty cell
            if (grid[i] == 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, LIGHTGRAY);
            // Test for snake head and body
            if (grid[i] == snakeLength) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, DARKGRAY);
            else if (grid[i] > 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, GRAY);
            // test for food
            if (grid[i] < 0) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, GREEN);
            // test for crash
            if (grid[i] == -2) DrawRectangle(gridXOrigin + (x * gridCellSize), gridYOrigin + (y * gridCellSize), gridCellSize, gridCellSize, RED);
        }
    }

    // Draw score
    std::string scoreText = "SCORE: " + std::to_string(snakeLength-1);
    DrawText(scoreText.c_str(), gridXOrigin, 15, 24, DARKGRAY);

    // Draw collision if gameover.
    if (status.gameover)
    {
        DrawRectangle(gridXOrigin + (playerX * gridCellSize), gridYOrigin + (playerY * gridCellSize), gridCellSize, gridCellSize, RED);
    }
}
// Gets keyboard input, tests our previous direction to ensure our new direction is valid, and updates the direction variable
void SnakeGame::getInput(int& dir, const int dirPrevious)
{

    if (IsKeyDown(KEY_UP))
    {
        if (dirPrevious != down)
            dir = up;
    }
    if (IsKeyDown(KEY_DOWN))
    {
        if (dirPrevious != up)
            dir = down;
    }
    if (IsKeyDown(KEY_LEFT))
    {
        if (dirPrevious != right)
            dir = left;
    }
    if (IsKeyDown(KEY_RIGHT))
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

// Selects a random location, checks if its free and spawns a food object here. Protects against a full grid and modifies game status on failure to place.
void SnakeGame::spawnFood(int grid[], const int gridSize, Status& status)
{
    // Spawn a random food.
    int food = rand() % (gridSize);
    int attempts = 0;
    int attemptsMax = 10;

    while (grid[food] != 0)
    {
        attempts++;
        if (attempts > attemptsMax)
        {
            // Walk the grid and place it. if we reach the end there is no valid space and we need to game over.
            for (int i = 0; i < gridSize; i++)
            {
                if (grid[i] == 0)
                {
                    grid[i] = -1;
                    return;
                }
            }
            // No valid space.
            status.gameover = true;
            return;
        }
        food = rand() % (gridSize);
    }
    grid[food] = -1;
    return;
}