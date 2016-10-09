#include "LogoScreen.h"

#include "../TetrisGame.h"
#include <assets/Bitmaps.h>

void LogoScreen::enter()
{
	clearScreen();
	drawBitmap(0, 0, BytewerkLogo, true);
}

void LogoScreen::update()
{
	if (timeSinceEntered() > T_LOGO_IDLE)
	{
		setNextScreen(getScreens().Idle);
	}

	if (isAnyKeyPressed() && (timeSinceEntered() > T_LOGO_MIN))
	{
		setNextScreen(getScreens().SelectLevel);
	}

}
