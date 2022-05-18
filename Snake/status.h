#pragma once
struct Status
{
    bool running = false;
    bool paused = true;
    bool gameStarted = false;
    SnakeGame* sg = nullptr;
};