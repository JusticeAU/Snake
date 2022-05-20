#include <string>
#include "raylib.h"
#include "status.h"
#include "SnakeGame.h"

class SnakeMenu
{
public:
	SnakeMenu();
	Status Update(Status status);
	void Draw();

private:
	int optionCount = 2;
	std::string options[2] = { "New Game", "Quit" };
	int cursor = 0;
	Color backgroundColour;
};