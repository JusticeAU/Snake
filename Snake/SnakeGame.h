#pragma once
#include "status.h"
#include "raylib.h"
#include "enums.h"
#include <random>
#include <time.h>

class SnakeGame
{
public:
    // Set up rendering offset for grid.
    int gridXOrigin;
    int gridYOrigin;

    // Create the 1D grid
    int gridColumns;
    int gridRows;
    int gridCellSize;
    int* grid;

    // Store player 'head' position
    int playerX = 2;
    int playerY = 4;
    int dir;
    int dirPrevious = -1;

    int frames = 0;
    int framesPerGameStep = 15;
    int snakeLength = 1;

    SnakeGame(const int screenWidth, const int screenHeight, const int gridRows, const int gridColumns, const int gridCellSize);
    ~SnakeGame();
	Status Update(Status status);
	void Draw(Status status);
    void getInput(int& dir, const int dirPrevious);
    int gridIndex(const int columnX, const int rowY, const int gridColumns, const int gridRows);
    void randomize();
    void spawnFood(int grid[], const int gridSize);
};