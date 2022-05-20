#pragma once
#include "status.h"
#include "raylib.h"
#include "enums.h"
#include <random>
#include <time.h>

class SnakeGame
{
public:
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
    int* grid;

    // Store player 'head' position
    int playerX = 5;
    int playerY = 5;
    int dir;
    int dirPrevious = -1;

    int frames = 0;
    int framesPerGameStep = 15;
    int snakeLength = 1;

    bool gameover = false;

    SnakeGame();
    ~SnakeGame();
	Status Update(Status status);
	void Draw();
    void getInput(int& dir, const int dirPrevious);
    int gridIndex(const int columnX, const int rowY, const int gridColumns, const int gridRows);
    void randomize();
    void spawnFood(int grid[], const int gridSize);
};