#include <string>
#include "raylib.h"
#include "status.h"

class SnakeMenu
{
public:
	SnakeMenu();
	void Update(Status& status);
	void Draw(Status& status);

private:
	int optionCount = 3;

	std::string options[3] = { "New Game", "Resume", "Quit" };

	int cursor = 0;

	Color backgroundColour {255,255,255,180}; // White with some transparency
};