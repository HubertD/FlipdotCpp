#include "SelectLevelScreen.h"

#include "../TetrisGame.h"

void SelectLevelScreen::enter()
{
	resetIdleTime();
	draw();
}

void SelectLevelScreen::update()
{
	auto& vars = getVariables();

	if (wasNextPressed())
	{
		if (++vars.startLevel > MAX_LEVEL)
		{
			vars.startLevel = MIN_LEVEL;
		}
		draw();
		resetIdleTime();
	}

	if (wasPreviousPressed())
	{
		if (--vars.startLevel < MIN_LEVEL)
		{
			vars.startLevel = MAX_LEVEL;
		}
		draw();
		resetIdleTime();
	}

	if (wasContinuePressed())
	{
		setNextScreen(getScreens().GetReady);
	}

	if (isIdleTimeout())
	{
		setNextScreen(getScreens().Logo);
	}

}

void SelectLevelScreen::draw()
{
	clearScreen();
	drawText(2, 1, (char*)"SELECT", Color::BLACK, Orientation::DEG_0, 1);
	drawText(2, 8, (char*)"LEVEL", Color::BLACK, Orientation::DEG_0, 2);
	drawChar(15, 17, '_');
	drawChar(15, 15, '0' + getVariables().startLevel);
}

void SelectLevelScreen::resetIdleTime()
{
	_tIdleSince = now();
}

bool SelectLevelScreen::isIdleTimeout()
{
	return (now() - _tIdleSince) >= IDLE_TIMEOUT_MS;
}
