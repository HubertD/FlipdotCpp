#include "TetrisField.h"
#include <Font.h>
#include <Framebuffer.h>
#include <games/Tetris/Screens/Main/TetrisInfoArea.h>

TetrisInfoArea::TetrisInfoArea(int level, int score, const TetrisBlock& nextBlock)
	: _level(level), _score(score), _nextBlock(nextBlock)
{
}

void TetrisInfoArea::draw(Framebuffer& fb, int x, int y, bool doInvert) const
{
	(void) doInvert;
	fb.draw(x, y, Rect(0, 0, WIDTH, HEIGHT), true);

	Font::drawChar(fb, x+LEVEL_X,   y+LEVEL_Y, 'L', Color::WHITE);
	Font::drawChar(fb, x+LEVEL_X+3, y+LEVEL_Y, ':', Color::WHITE);
	Font::drawChar(fb, x+LEVEL_X+7, y+LEVEL_Y, '0'+_level, Color::WHITE);

	if (_score < SCORE_SHOW_K)
	{
		Font::drawNumber(fb, x+SCORE_X, y+SCORE_Y+3, _score, Color::WHITE, Orientation::DEG_90);
	} else {
		Font::drawNumber(fb, x+SCORE_X, y+SCORE_Y-2, _score/1000, Color::WHITE, Orientation::DEG_90);
		Font::drawChar(fb, x+SCORE_X, y+SCORE_Y-1, 'K', Color::WHITE, Orientation::DEG_90);
	}

	_nextBlock.draw(fb, x+NEXT_BLOCK_X, y+NEXT_BLOCK_Y, true);
}
