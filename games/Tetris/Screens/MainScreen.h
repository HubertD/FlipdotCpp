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
		} state = State::RUNNING;

		static const int FIELD_X = 0;
		static const int FIELD_Y = 0;
		static const int NEXT_BLOCK_X = 22;
		static const int NEXT_BLOCK_Y = 6;
		static const int LINE_SCORE_MULT = 2;
		static const unsigned TIMEOUT_GAME_OVER = 2000;
		static const unsigned DELETED_ROWS_BLINK_COUNT = 3;
		static const unsigned DELETED_ROWS_BLINK_INTERVAL = 200;

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

		void updateGamepad();
		void makeStepIfDue();
		void checkForFullRows();
		void removeFullRows();
		int calcPointsForDeletedRows(int deletedRows);
		bool checkGameOver();
		bool isMoveAllowed(TetrisBlock::Move move);
		bool moveIfAllowed(TetrisBlock::Move move);
		void switchToNextBlock();
		void draw();
		void drawLevel();
		void drawScore();
		void drawField();
		void drawNextBlock();
		void updateStepInterval();

};
