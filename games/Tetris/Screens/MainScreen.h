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

		enum class State {
			RUNNING,
			GAME_OVER,
			ROWS_BLINKING
		} _state = State::RUNNING;

		static const int FIELD_X = 0;
		static const int FIELD_Y = 0;
		static const int NEXT_BLOCK_X = 22;
		static const int NEXT_BLOCK_Y = 6;
		static const int SCORE_X = 24;
		static const int SCORE_Y = 42;
		static const unsigned SCORE_SHOW_K = 10000;

		static const unsigned TIMEOUT_GAME_OVER = 2000;
		static const unsigned DELETED_ROWS_BLINK_COUNT = 3;
		static const unsigned DELETED_ROWS_BLINK_INTERVAL = 200;

		static const unsigned MAX_LEVEL = 9;
		static const unsigned ROWS_FOR_LEVEL_UP = 10;

		static const int STEP_INTERVAL_LEVEL_0 = 400;
		static const int STEP_INTERVAL_LEVEL_DELTA = -30;

		static const int POINTS_1_ROW_FACTOR  =   40;
		static const int POINTS_2_ROWS_FACTOR =  100;
		static const int POINTS_3_ROWS_FACTOR =  300;
		static const int POINTS_4_ROWS_FACTOR = 1200;
		static const int POINTS_PER_STEP_FACTOR =  2;



		unsigned _score = 0;
		unsigned _scoreBuf = 0;
		unsigned _level = 0;
		unsigned _destructedRows = 0;
		unsigned _stepInterval = 0;
		unsigned _tNextStep = 0;
		unsigned _tGameOverWait = 0;
		unsigned _tBlinkNextToggle = 0;
		unsigned _blinkTogglesRemaining = 0;

		TetrisField _field;
		TetrisBlock _currentBlock;
		TetrisBlock _nextBlock;

		void updateStateGameRunning();
		void updateStateGameOver();
		void updateStateRowsBlinking();

		void checkCommands();
		void makeStepIfDue();
		void checkForFullRows();
		void removeFullRows();
		int  calcPointsForDeletedRows(int deletedRows);
		void checkGameOver();
		bool moveIfAllowed(TetrisBlock::Move move);
		void switchToNextBlock();
		void draw();
		void updateLevel();

};
