#pragma once
struct Status
{
    bool paused { true };
    bool gameover{ false };
    bool restartRequested { false };
    bool quitRequested { false };
};