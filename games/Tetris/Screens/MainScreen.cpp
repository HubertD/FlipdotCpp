#include <games/Tetris/Screens/MainScreen.h>
#include <stdlib.h>

#include <games/Tetris/TetrisVariables.h>

void MainScreen::enter()
{
	srand(now());
	_score = 13307;
	_level = getVariables().startLevel;
	_destructedLines = 0;
}

void MainScreen::update()
{
	draw();
}

void MainScreen::draw()
{
	clearScreen();
	drawLevel();
	drawScore();
	drawField();
	drawNextBlock();
}

void MainScreen::drawLevel()
{
	drawChar(23, 0, 'L');
	drawChar(26, 0, ':');
	drawChar(29, 0, '0'+_level);
}

void MainScreen::drawScore()
{
	if (_score < 10000) {
		drawNumber(26, 43, _score, FlipdotColor::BLACK, Orientation::DEG_90);
	} else {
		drawNumber(26, 38, _score, FlipdotColor::BLACK, Orientation::DEG_90);
		drawChar(26, 39, 'K', FlipdotColor::BLACK, Orientation::DEG_90);
	}
}

void MainScreen::drawField()
{
	for (int fieldY=0; fieldY<FIELD_HEIGHT; fieldY++)
	{
		for (int fieldX=0; fieldX<FIELD_WIDTH; fieldX++)
		{
			drawFieldPoint(fieldX, fieldY, getFieldPoint(fieldX, fieldY) ? FlipdotColor::BLACK : FlipdotColor::WHITE);
		}
	}
}

void MainScreen::drawFieldPoint(int fieldX, int fieldY, FlipdotColor color)
{
	auto px = FIELD_X + (fieldX*FIELD_POINT_WIDTH);
	auto py = FIELD_Y + (fieldY*FIELD_POINT_WIDTH);
	bool value = (color == FlipdotColor::BLACK);
	drawRect(px, py, FIELD_POINT_WIDTH, FIELD_POINT_HEIGHT, value);
}

void MainScreen::drawNextBlock()
{
}

bool MainScreen::getFieldPoint(int fieldX, int fieldY)
{
	return (_field[fieldY] & (1<<fieldX)) != 0;
}
