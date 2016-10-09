#include "GetReadyScreen.h"
#include "../TetrisScreens.h"

void GetReadyScreen::update()
{
	if (timeSinceEntered() > TIMEOUT)
	{
		setNextScreen(getScreens().Logo);
	}
}

void GetReadyScreen::enter()
{
	clearScreen();
	drawText(2, 1, (char*)"GET", FlipdotColor::BLACK, Orientation::DEG_0, 1);
	drawText(2, 8, (char*)"READY!", FlipdotColor::BLACK, Orientation::DEG_0, 1);
}
