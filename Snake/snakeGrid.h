#pragma once
#include <random>
#include <time.h>

// Calculates an index for a 1D array based on 2D coordinates.
// If the index is outout bounds, it will return -1.
int gridIndex(const int columnX, const int rowY, const int gridColumns, const int gridRows)
{
	int index = (rowY * gridColumns) + columnX;
	if (index < 0 || index >= gridColumns * gridRows) return -1;
	else return index;
}

// Sets the random seed for the game based on time to make every game different.
void randomize()
{
    srand(time(nullptr));
}

// Selects a random location, checks if its free and spawns a food object here.
void spawnFood(int grid[], const int gridSize)
{
    // Spawn a random food.
    int food = rand() % (gridSize);

    while (grid[food] != 0)
    {
        food = rand() % (gridSize);
    }
    grid[food] = -1;
}