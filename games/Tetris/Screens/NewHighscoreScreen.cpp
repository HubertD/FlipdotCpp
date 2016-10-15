#include "NewHighscoreScreen.h"
#include <Gamepad.h>
#include "../TetrisVariables.h"
#include "../TetrisScreens.h"

void NewHighscoreScreen::enter()
{
	for (int i=0; i<NUM_CHARS; i++)
	{
		_name[i] ='_';
	}
	_cursorPosition = 0;
	draw();
}

void NewHighscoreScreen::update()
{
	auto &gp = getGamepad();

	if (gp.West.hasDownEvent()) {

		if (--_cursorPosition < 0) {
			_cursorPosition = NUM_CHARS-1;
		}

	}

	if (gp.East.hasDownEvent())
	{
		if (++_cursorPosition >= NUM_CHARS)
		{
			_cursorPosition = 0;
		}
	}

	if (gp.North.hasPressEvent() || gp.South.hasPressEvent())
	{
		int direction = gp.South.hasPressEvent() ? +1 : -1;
		char ch = _name[_cursorPosition];
		ch += direction;
		if (ch > 'Z') { ch = 'A'; }
		if (ch < 'A') { ch = 'Z'; }
		_name[_cursorPosition] = ch;
	}

	if (gp.A.hasPressEvent())
	{
		getVariables().highScorer = _name;
		setNextScreen(getScreens().Logo);
	}

	draw();
}

void NewHighscoreScreen::draw()
{
	clearScreen();
	drawText(2, 1, (char*)"HIGH", Color::BLACK, Orientation::DEG_0, 1);
	drawText(2, 8, (char*)"SCORE!", Color::BLACK, Orientation::DEG_0, 1);
	drawNumber(31, 15, getVariables().highScore);
	drawText(2, 22, (char*)"NAME:");
	drawText(2, 29, _name);
}
