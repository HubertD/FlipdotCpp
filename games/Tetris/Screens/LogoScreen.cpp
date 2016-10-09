#include "LogoScreen.h"

#include "../TetrisGame.h"
#include <assets/Bitmaps.h>

void LogoScreen::enter()
{
	auto& gfx = _game.gfx();
	gfx.clear();
	gfx.drawBitmap(0, 0, BytewerkLogo, true);
}

void LogoScreen::update()
{
	auto& gamepad = _game.gamepad();

	if (gamepad.isAnyKeyPressed() && (timeSinceEntered() > T_LOGO_MIN))
	{
		_game.setNextScreen(_game.screens.SelectLevel);
		return;
	}

	if (timeSinceEntered() > T_LOGO_IDLE)
	{
		_game.setNextScreen(_game.screens.Idle);
	}

}
