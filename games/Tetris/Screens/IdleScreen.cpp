#include "IdleScreen.h"

#include "../TetrisGame.h"
#include "../TetrisScreens.h"

#include <assets/Bitmaps.h>

void IdleScreen::enter()
{
	auto& gfx = getGfx();
	gfx.clear();
	gfx.drawText(2, 1, (char*)"TETRIS", FlipdotColor::BLACK, Orientation::DEG_0, 1);
	gfx.drawBitmap(3, 12, StatsQrCode);
}

void IdleScreen::update()
{
	if (isAnyKeyPressed())
	{
		setNextScreen(getScreens().SelectLevel);
		return;
	}
}
