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

		switchToNextBlock();
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
	checkGamepadMoveEvent(gp.West,    TetrisBlock::Move::LEFT);
	checkGamepadMoveEvent(gp.East,    TetrisBlock::Move::RIGHT);
	checkGamepadMoveEvent(gp.South,   TetrisBlock::Move::DOWN);
	checkGamepadRotateEvent(gp.A,     TetrisBlock::Move::ROTATE_LEFT);
	checkGamepadRotateEvent(gp.B,     TetrisBlock::Move::ROTATE_RIGHT);
	checkGamepadRotateEvent(gp.North, TetrisBlock::Move::ROTATE_RIGHT);
}

void MainScreen::checkGamepadMoveEvent(GamepadKey& key, TetrisBlock::Move move)
{
	if (!key.hasPressEvent()) { return; }
	if (!isMovePossible(_currentBlock, move)) { return; }

	_currentBlock.move(move);
	if (move == TetrisBlock::Move::DOWN)
	{
		_score.scoreStep();
	}
}


void MainScreen::checkGamepadRotateEvent(GamepadKey& key, TetrisBlock::Move move)
{
	if (!key.hasPressEvent()) { return; }

	auto block = _currentBlock;

	if (!isMovePossible(block, move) && (block.getPositionX() == -1))
	{
		block.move(TetrisBlock::Move::RIGHT);
	}

	for (int i=0; i<4; i++)
	{
		if (!isMovePossible(block, move) && (block.getPositionX() == (_field.COLUMNS-i)))
		{
			block.move(TetrisBlock::Move::LEFT);
		}
	}

	if (isMovePossible(block, move))
	{
		block.move(move);
		_currentBlock = block;
	}
}

void MainScreen::makeIntervalStep()
{
	if (isMovePossible(_currentBlock, TetrisBlock::Move::DOWN)) {
		_currentBlock.move(TetrisBlock::Move::DOWN);
	} else {

		if (isMergePossible()) {
			_currentBlock.merge(_field);
			_score.scoreMerge();
			if (!_field.hasFullRows())
			{
				switchToNextBlock();
			}
		} else {
			setGameOver();
		}

	}

	_tNextStep = now() + _score.getStepInterval();
}

bool MainScreen::isMovePossible(TetrisBlock &block, TetrisBlock::Move move)
{
	auto copy = block;
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

