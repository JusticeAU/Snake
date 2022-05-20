#pragma once
struct Status
{
    bool paused = true;
    bool firstStarted = false;
    bool restartRequested = false;
    bool quitRequested = false;
};