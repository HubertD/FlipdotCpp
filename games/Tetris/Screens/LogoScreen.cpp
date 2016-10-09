#include "LogoScreen.h"

#include "../TetrisGame.h"
#include <assets/Bitmaps.h>

void LogoScreen::enter()
{
	auto& gfx = getGfx();
	gfx.clear();
	gfx.drawBitmap(0, 0, BytewerkLogo, true);
}

void LogoScreen::update()
{
	auto& gamepad = getGamepad();

	if (gamepad.isAnyKeyPressed() && (timeSinceEntered() > T_LOGO_MIN))
	{
		setNextScreen(getScreens().SelectLevel);
		return;
	}

	if (timeSinceEntered() > T_LOGO_IDLE)
	{
		setNextScreen(getScreens().Idle);
	}

}
