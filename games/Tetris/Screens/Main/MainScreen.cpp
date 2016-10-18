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

	processFullRows();
}

void MainScreen::processFullRows()
{
	if (_field.hasFullRows())
	{
		_blinkTogglesRemaining = 1 + 2 * DELETED_ROWS_BLINK_COUNT;
		_tBlinkNextToggle = 0;
		_state = State::ROWS_BLINKING;
		updateStateRowsBlinking();
	}
}

void MainScreen::updateStateGameOver()
{
	if (_tGameOverWait >= now())
	{
		return;
	}

	if (_score.getScore() > getVariables().highScore)
	{
		getVariables().highScore = _score.getScore();
		setNextScreen(getScreens().NewHighscore);
	} else {
		setNextScreen(getScreens().TryAgain);
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
		_field.setDrawFullRowsInverted(false);
		_tBlinkNextToggle = 0;

		removeFullRows();
		_state = State::RUNNING;
		_tNextStep = now() + _score.getStepInterval();

	} else {
		_tBlinkNextToggle = now() + DELETED_ROWS_BLINK_INTERVAL;
		_field.setDrawFullRowsInverted((_blinkTogglesRemaining % 2) == 0);
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
		_currentBlock.move(move);
	}
}

void MainScreen::makeIntervalStep()
{
	if (isMovePossible(TetrisBlock::Move::DOWN)) {
		_currentBlock.move(TetrisBlock::Move::DOWN);
		_score.scoreStep();
	} else {

		if (isMergePossible()) {
			_currentBlock.merge(_field);
			_score.scoreMerge();
			switchToNextBlock();
		} else {
			setGameOver();
		}

	}

	_tNextStep = now() + _score.getStepInterval();
}

bool MainScreen::isMovePossible(TetrisBlock::Move move)
{
	auto copy = _currentBlock;
	copy.move(move);
	return !copy.wouldCollide(_field);
}

bool MainScreen::isMergePossible()
{
	return (!_currentBlock.isAboveTopOfField()) && (!_currentBlock.wouldCollide(_field));
}

void MainScreen::switchToNextBlock()
{
	_currentBlock = _nextBlock;
	_currentBlock.setPosition(((TetrisField::COLUMNS / 2) - 1), -3);
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

void MainScreen::setGameOver()
{
	getVariables().lastScore = _score.getScore();
	_state = State::GAME_OVER;
	_tGameOverWait = now() + WAIT_AFTER_GAME_OVER;
}

void MainScreen::draw()
{
	clearScreen();
	drawObject(FIELD_X, FIELD_Y, _field);
	drawObject(INFO_AREA_X, INFO_AREA_Y, TetrisInfoArea(_score.getLevel(), _score.getScore(), _nextBlock));
	drawObject(FIELD_X, FIELD_Y, _currentBlock);
}

