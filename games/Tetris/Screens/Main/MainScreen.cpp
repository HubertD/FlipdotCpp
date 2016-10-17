#include "MainScreen.h"

#include <stdlib.h>
#include <Gamepad.h>

#include "TetrisInfoArea.h"
#include "TetrisBlock.h"
#include <games/Tetris/TetrisVariables.h>
#include <games/Tetris/TetrisScreens.h>

MainScreen::MainScreen(TetrisGame& game)
  : TetrisScreenBase(game),
	_currentBlock(TetrisBlock::createRandomBlock()),
	_nextBlock(TetrisBlock::createRandomBlock())
{
}

void MainScreen::enter()
{
	srand(now());

	_field.clear();
	_score.init(getVariables().startLevel);
	_tNextStep = now();

	getVariables().lastScore = 0;

	_state = State::RUNNING;
	switchToNextBlock();
}

void MainScreen::update()
{
	switch (_state)
	{
		case State::RUNNING:
			updateStateGameRunning();
			break;

		case State::GAME_OVER:
			updateStateGameOver();
			break;

		case State::ROWS_BLINKING:
			updateStateRowsBlinking();
			break;
	}
	draw();
}

void MainScreen::updateStateGameRunning()
{
	checkGamepadEvents();

	if (now() >= _tNextStep)
	{
		makeIntervalStep();
	}

	checkForFullRows();
	checkGameOver();
}

void MainScreen::checkForFullRows()
{
	if (_field.hasFullRows())
	{
		_state = State::ROWS_BLINKING;
		_blinkTogglesRemaining = 1 + 2 * DELETED_ROWS_BLINK_COUNT;
		_tBlinkNextToggle = 0;
		updateStateRowsBlinking();
	}
}

void MainScreen::updateStateGameOver()
{
	if (now() > _tGameOverWait)
	{
		if (_score.getScore() > getVariables().highScore)
		{
			getVariables().highScore = _score.getScore();
			setNextScreen(getScreens().NewHighscore);
		} else {
			setNextScreen(getScreens().TryAgain);
		}
	}
}

void MainScreen::updateStateRowsBlinking()
{
	if (_tBlinkNextToggle >= now())
	{
		return;
	}

	if (--_blinkTogglesRemaining == 0)
	{
		_field.setInvertFullRows(false);
		_tBlinkNextToggle = 0;

		removeFullRows();
		_state = State::RUNNING;
		_tNextStep = now() + _score.getStepInterval();

	} else {
		_tBlinkNextToggle = now() + DELETED_ROWS_BLINK_INTERVAL;
		_field.setInvertFullRows((_blinkTogglesRemaining % 2) == 0);
	}
}

void MainScreen::checkGamepadEvents()
{
	auto& gp = getGamepad();
	checkGamepadPressEvent(gp.West,  TetrisBlock::Move::LEFT);
	checkGamepadPressEvent(gp.East,  TetrisBlock::Move::RIGHT);
	checkGamepadPressEvent(gp.A,     TetrisBlock::Move::ROTATE_LEFT);
	checkGamepadPressEvent(gp.B,     TetrisBlock::Move::ROTATE_RIGHT);
	checkGamepadPressEvent(gp.North, TetrisBlock::Move::ROTATE_RIGHT);
	checkGamepadPressEvent(gp.South, TetrisBlock::Move::DOWN);
}

void MainScreen::checkGamepadPressEvent(GamepadKey& key, TetrisBlock::Move move)
{
	if (key.hasPressEvent() && isMovePossible(move))
	{
		_currentBlock.makeMove(move);
	}
}

bool MainScreen::isMovePossible(TetrisBlock::Move move)
{
	auto copy = _currentBlock;
	copy.makeMove(move);
	return !copy.doesCollide(_field);
}

void MainScreen::makeIntervalStep()
{
	if (isMovePossible(TetrisBlock::Move::DOWN)) {
		_currentBlock.makeMove(TetrisBlock::Move::DOWN);
		_score.scoreStep();
	} else {
		_currentBlock.merge(_field);
		_score.scoreMerge();
		switchToNextBlock();
	}

	_tNextStep = now() + _score.getStepInterval();
}

void MainScreen::switchToNextBlock()
{
	_currentBlock = _nextBlock;
	_currentBlock.setX((TetrisField::COLUMNS / 2) - 1);
	_currentBlock.setY(-3);
	_nextBlock = TetrisBlock::createRandomBlock();
}

void MainScreen::removeFullRows()
{
	int deletedRows = _field.deleteFullRows();
	if (deletedRows>0)
	{
		_score.scoreDeleteRows(deletedRows);
	}
}

void MainScreen::checkGameOver()
{
	if (_currentBlock.doesCollide(_field))
	{
		getVariables().lastScore = _score.getScore();
		_state = State::GAME_OVER;
		_tGameOverWait = now() + WAIT_AFTER_GAME_OVER;
	}
}

void MainScreen::draw()
{
	clearScreen();
	drawObject(FIELD_X, FIELD_Y, _field);
	drawObject(INFO_AREA_X, INFO_AREA_Y, TetrisInfoArea(_score.getLevel(), _score.getScore(), _nextBlock));
	_currentBlock.draw(getFramebuffer(), FIELD_X, FIELD_Y, 2, 2, Color::BLACK);
}
