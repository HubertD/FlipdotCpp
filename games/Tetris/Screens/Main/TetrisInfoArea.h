#pragma once

#include <IDrawable.h>
#include "TetrisBlock.h"

class TetrisInfoArea : public IDrawable
{
	public:
		TetrisInfoArea(int level, int score, const TetrisBlock &nextBlock);
		void draw(Framebuffer &fb, int x, int y, bool doInvert=false) const override;

	private:

		static const int WIDTH = 12;
		static const int HEIGHT = 40;

		static const int LEVEL_X = 1;
		static const int LEVEL_Y = 1;

		static const int SCORE_X = 4;
		static const int SCORE_Y = HEIGHT-1;
		static const int SCORE_SHOW_K = 10000;

		static const int NEXT_BLOCK_X = 2;
		static const int NEXT_BLOCK_Y = 6;



		int _level;
		int _score;
		const TetrisBlock _nextBlock;
};
