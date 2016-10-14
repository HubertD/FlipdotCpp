#include "LogoScreen.h"

#include "../TetrisGame.h"
#include <assets/Bitmaps.h>

void LogoScreen::enter()
{
	clearScreen();
	drawObject(0, 8, BytewerkLogo, true);
	drawText(1, 1, (char*)"BYTEWERK");
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
