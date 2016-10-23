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
	_tNextBlinkToggle = now() + BLINK_INTERVAL;
	_showBlinkingChar = true;
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

	if (gp.North.hasPressEvent())
	{
		_name[_cursorPosition] = getPreviousChar(_name[_cursorPosition]);
		_showBlinkingChar = true;
		_tNextBlinkToggle = now() + BLINK_INTERVAL;
	}

	if (gp.South.hasPressEvent())
	{
		_name[_cursorPosition] = getNextChar(_name[_cursorPosition]);
		_showBlinkingChar = true;
		_tNextBlinkToggle = now() + BLINK_INTERVAL;
	}

	if (gp.A.hasPressEvent())
	{
		getVariables().highScorer = _name;
		setNextScreen(getScreens().Logo);
	}

	if (now() >= _tNextBlinkToggle)
	{
		_showBlinkingChar = !_showBlinkingChar;
		_tNextBlinkToggle = now() + BLINK_INTERVAL;
	}


	draw();
}


char NewHighscoreScreen::getNextChar(char ch)
{
	switch (ch)
	{
		case 'Z': return '0';
		case '9': return ':';
		case ':': return '!';
		case '!': return '_';
		case '_': return ' ';
		case ' ': return 'A';
		default:  return ch+1;
	}
}

char NewHighscoreScreen::getPreviousChar(char ch)
{
	switch (ch)
	{
		case 'A': return ' ';
		case ' ': return '_';
		case '_': return '!';
		case '!': return ':';
		case ':': return '9';
		case '0': return 'Z';
		default:  return ch-1;
	}
}

void NewHighscoreScreen::draw()
{
	clearScreen();
	drawText(2, 1, (char*)"HIGH", Color::BLACK, Orientation::DEG_0, 1);
	drawText(2, 8, (char*)"SCORE!", Color::BLACK, Orientation::DEG_0, 1);
	drawNumber(31, 15, getVariables().highScore);
	drawText(2, 22, (char*)"NAME:");

	char displayName[NUM_CHARS];
	for (int i=0; i<NUM_CHARS; i++)
	{
		if ( (i!=_cursorPosition) || _showBlinkingChar)
		{
			displayName[i] = _name[i];
		} else {
			displayName[i] = ' ';
		}
	}
	drawText(2, 29, displayName);
}
