#pragma once

#include <games/Tetris/TetrisScreenBase.h>
#include <games/Tetris/TetrisField.h>

class MainScreen: public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;

		void enter() override;
		void update() override;

	private:

		static const int FIELD_X = 0;
		static const int FIELD_Y = 0;

		unsigned _score = 0;
		unsigned _level = 0;
		unsigned _destructedLines = 0;
		TetrisField _field;

		void draw();
		void drawLevel();
		void drawScore();
		void drawField();
		void drawNextBlock();

};
