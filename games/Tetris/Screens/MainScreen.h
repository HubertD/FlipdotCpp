#pragma once

#include <games/Tetris/TetrisScreenBase.h>

class MainScreen: public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;

		void enter() override;
		void update() override;

	private:

		static const int FIELD_X = 0;
		static const int FIELD_Y = 0;
		static const int FIELD_WIDTH = 10;
		static const int FIELD_HEIGHT = 20;
		static const int FIELD_POINT_WIDTH = 2;
		static const int FIELD_POINT_HEIGHT = 2;

		unsigned _score = 0;
		unsigned _level = 0;
		unsigned _destructedLines = 0;
		uint16_t _field[FIELD_HEIGHT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0xFFFF };

		bool getFieldPoint(int fieldX, int fieldY);
		void draw();
		void drawLevel();
		void drawScore();
		void drawField();
		void drawFieldPoint(int fieldX, int fieldY, FlipdotColor color);
		void drawNextBlock();

};
