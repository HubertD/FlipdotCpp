#include <games/Tetris/Screens/TryAgainScreen.h>

#include "../TetrisScreens.h"
#include "../TetrisVariables.h"
#include <assets/Bitmaps.h>

void TryAgainScreen::enter()
{
	draw();
}

void TryAgainScreen::update()
{
	if (timeSinceEntered() < T_IGNORE_KEYS)
	{
		return;
	}

	if (wasAnyKeyPressed())
	{
		setNextScreen(getScreens().SelectLevel);
		return;
	}

	if (timeSinceEntered() > T_GOTO_LOGO)
	{
		setNextScreen(getScreens().Logo);
		return;
	}

}

void TryAgainScreen::draw()
{
	clearScreen();
	drawObject(13, 15, Heart, true);
	drawText(11, 1, (char*)"TRY", Color::BLACK, Orientation::DEG_0, 1);
	drawText( 6, 8, (char*)"AGAIN", Color::BLACK, Orientation::DEG_0, 1);

	drawNumber(31, 23, getVariables().lastScore, Color::BLACK, Orientation::DEG_0, 0);
	drawNumber(31, 29, getVariables().highScore, Color::BLACK, Orientation::DEG_0, 0);
	drawText(11, 35, (char*)"XOR", Color::BLACK, Orientation::DEG_0, 1);
}
