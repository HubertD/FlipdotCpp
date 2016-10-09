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

	if (wasRightOrUpPressed())
	{
		if (++vars.startLevel > MAX_LEVEL)
		{
			vars.startLevel = MIN_LEVEL;
		}
		draw();
		resetIdleTime();
	}

	if (wasLeftOrDownPressed())
	{
		if (--vars.startLevel < MIN_LEVEL)
		{
			vars.startLevel = MAX_LEVEL;
		}
		draw();
		resetIdleTime();
	}

	if (wasStartOrSelectPressed())
	{
		setNextScreen(getScreens().Logo);
	}

	if (isIdleTimeout())
	{
		setNextScreen(getScreens().Logo);
	}

}

void SelectLevelScreen::draw()
{
	auto& gfx = getGfx();

	gfx.clear();
	gfx.drawText(2, 1, (char*)"SELECT", FlipdotColor::BLACK, Orientation::DEG_0, 1);
	gfx.drawText(2, 8, (char*)"LEVEL", FlipdotColor::BLACK, Orientation::DEG_0, 2);
	gfx.drawChar(15, 17, '_');
	gfx.drawChar(15, 15, '0' + getVariables().startLevel);
}

void SelectLevelScreen::resetIdleTime()
{
	_tIdleSince = now();
}

bool SelectLevelScreen::isIdleTimeout()
{
	return (now() - _tIdleSince) >= IDLE_TIMEOUT_MS;
}
