#pragma once
#include "raylib.h"
#include "enums.h"

// Gets keyboard input, tests our previous direction to ensure our new direction is valid, and updates the direction variable
void getInput(int &dir, const int dirPrevious)
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