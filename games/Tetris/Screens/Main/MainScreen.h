#pragma once

#include <games/Tetris/TetrisScreenBase.h>
#include "TetrisField.h"
#include "TetrisBlock.h"
#include "TetrisScore.h"

class GamepadKey;

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

		static const int INFO_AREA_X = 20;
		static const int INFO_AREA_Y = 0;

		static const unsigned WAIT_AFTER_GAME_OVER = 2000;
		static const unsigned DELETED_ROWS_BLINK_COUNT = 3;
		static const unsigned DELETED_ROWS_BLINK_INTERVAL = 200;

		unsigned _tNextStep = 0;
		unsigned _tGameOverWait = 0;
		unsigned _tBlinkNextToggle = 0;
		unsigned _blinkTogglesRemaining = 0;

		TetrisScore _score;
		TetrisField _field;
		TetrisBlock _currentBlock;
		TetrisBlock _nextBlock;

		void updateStateGameRunning();
		void updateStateGameOver();
		void updateStateRowsBlinking();

		void checkGamepadEvents();
		void checkGamepadPressEvent(GamepadKey &key, TetrisBlock::Move move);
		bool isMovePossible(TetrisBlock::Move move);

		void makeIntervalStep();
		void checkForFullRows();
		void removeFullRows();
		void checkGameOver();
		void switchToNextBlock();
		void draw();

};
