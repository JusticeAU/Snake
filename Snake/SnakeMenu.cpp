#include "SnakeMenu.h"
#include <iostream>

SnakeMenu::SnakeMenu()
{
	backgroundColour.a = 200;
}

Status SnakeMenu::Update(Status status)
{
	if (IsKeyPressed(KEY_UP))
	{
		cursor--;
		if (cursor < 0)
			cursor = optionCount - 1;
	}

	if (IsKeyPressed(KEY_DOWN))
	{
		cursor++;
		if (cursor == optionCount)
			cursor = 0;
	}

	if (IsKeyPressed(KEY_ENTER))
	{
		switch (cursor)
		{
		case 0:
			status.restartRequested = true;
			status.paused = false;
			status.gameover = false;
			break;
		case 1:
			if(!status.gameover)
				status.paused = false;
			break;
		case 2:
			status.quitRequested = true;
			break;
		}
	}
	return status;
}
void SnakeMenu::Draw(Status status)
{
	// Fade the background
	DrawRectangle(0, 0, 1280, 720, backgroundColour);

	// Draw menu options
	for (int i = 0; i < optionCount; i++)
	{
		if (i == cursor)
		{
			char* line = new char[100];
			strcpy(line, options[i].c_str());
			strcat(line, " <");
			DrawText(line, 50, 50 + (i * 100), 45, DARKGRAY);
		}
		else
			DrawText(options[i].c_str(), 50, 50 + (i * 100), 40, GRAY);
	}

	// Draw controls
	DrawText("Controls", 50, 600, 20, GRAY);
	DrawText("Arrows: Change snake direction / menu options", 50, 625, 20, GRAY);
	DrawText("Space: Select menu option", 50, 650, 20, GRAY);
	DrawText("P: Pause", 50, 675, 20, GRAY);

	if(status.gameover)
		DrawText("Game Over!", 540, 200, 30, MAROON);
}