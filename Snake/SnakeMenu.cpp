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
			std::cout << "Selected new game" << std::endl;
			status.paused = false;
			if (status.gameStarted)
			{
				status.restartGame = true;
			}
			else status.gameStarted = true;
			break;
		case 1:
			std::cout << "Quitting" << std::endl;
			std::quick_exit(0);
			break;
		}
	}
	return status;
}
void SnakeMenu::Draw()
{
	DrawRectangle(0, 0, 1280, 720, backgroundColour);

	for (int i = 0; i < optionCount; i++)
	{
		if (i == cursor)
		{
			char* line = new char[100];
			strcpy(line, options[i].c_str());
			strcat(line, " <");
			DrawText(line, 50, 50 + (i * 50), 20, RED);
		}
		else
			DrawText(options[i].c_str(), 50, 50 + (i * 50), 20, RED);
	}

}