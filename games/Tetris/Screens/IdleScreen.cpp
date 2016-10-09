#include "IdleScreen.h"

#include "../TetrisGame.h"
#include <assets/Bitmaps.h>

void IdleScreen::enter()
{
	auto& gfx = _game.gfx();
	gfx.clear();
	gfx.drawText(2, 1, (char*)"TETRIS", FlipdotColor::BLACK, Orientation::DEG_0, 1);
	gfx.drawBitmap(3, 12, StatsQrCode);
}

void IdleScreen::update()
{
	if (_game.gamepad().isAnyKeyPressed())
	{
		_game.setNextScreen(_game.screens.SelectLevel);
		return;
	}
}
