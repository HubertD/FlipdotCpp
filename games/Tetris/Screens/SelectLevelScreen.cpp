#include "SelectLevelScreen.h"

#include "../TetrisGame.h"

void SelectLevelScreen::enter()
{
	draw();
}

void SelectLevelScreen::update()
{
	if (timeSinceEntered() > 10000)
	{
		_game.setNextScreen(_game.screens.Logo);
		return;
	}
}

void SelectLevelScreen::draw()
{
	auto& gfx = _game.gfx();
	gfx.clear();
	gfx.drawText(2, 1, (char*)"SELECT", FlipdotColor::BLACK, Orientation::DEG_0, 1);
	gfx.drawText(2, 8, (char*)"LEVEL", FlipdotColor::BLACK, Orientation::DEG_0, 2);
	gfx.drawChar(15, 17, '_');
	gfx.drawChar(15, 15, '0');
	/*
	  display_draw_character(15, 15, PFC_0+startLevel, 1, CHARACTER_ROTATION_NONE);
	*/
}
