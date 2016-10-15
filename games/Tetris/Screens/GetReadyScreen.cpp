#include "GetReadyScreen.h"
#include "../TetrisScreens.h"

void GetReadyScreen::update()
{
	if (timeSinceEntered() > TIMEOUT)
	{
		setNextScreen(getScreens().Main);
	}
}

void GetReadyScreen::enter()
{
	clearScreen();
	drawText(2, 1, (char*)"GET", Color::BLACK, Orientation::DEG_0, 1);
	drawText(2, 8, (char*)"READY!", Color::BLACK, Orientation::DEG_0, 1);
}
