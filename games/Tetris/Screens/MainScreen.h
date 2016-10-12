#pragma once

#include <games/Tetris/TetrisScreenBase.h>
#include <games/Tetris/TetrisField.h>
#include <games/Tetris/TetrisBlock.h>

class MainScreen: public TetrisScreenBase
{
	public:
		MainScreen(TetrisGame &game);

		void enter() override;
		void update() override;

	private:

		static const int FIELD_X = 0;
		static const int FIELD_Y = 0;

		unsigned _score = 0;
		unsigned _level = 0;
		unsigned _destructedLines = 0;
		unsigned _stepInterval = 1000;
		unsigned _tNextStep = 0;
		TetrisField _field;
		TetrisBlock _currentBlock;
		TetrisBlock _nextBlock;

		void updateGamepad();
		bool isMoveAllowed(TetrisBlock::Move move);
		bool moveIfAllowed(TetrisBlock::Move move);
		void draw();
		void drawLevel();
		void drawScore();
		void drawField();
		void drawNextBlock();

};
