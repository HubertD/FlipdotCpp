#include "IdleScreen.h"

#include "../TetrisGame.h"
#include <assets/Bitmaps.h>
#include "../TetrisScreens.h"

void IdleScreen::enter()
{
	auto& gfx = getGfx();
	gfx.clear();
	gfx.drawText(2, 1, (char*)"TETRIS", FlipdotColor::BLACK, Orientation::DEG_0, 1);
	gfx.drawBitmap(3, 12, StatsQrCode);
}

void IdleScreen::update()
{
	if (getGamepad().isAnyKeyPressed())
	{
		setNextScreen(getScreens().SelectLevel);
		return;
	}
}
