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
	checkCommands();
	makeStepIfDue();
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

void MainScreen::checkCommands()
{
	auto& gp = getGamepad();

	if (gp.West.hasPressEvent())
	{
		moveIfAllowed(TetrisBlock::Move::LEFT);
	}

	if (gp.East.hasPressEvent())
	{
		moveIfAllowed(TetrisBlock::Move::RIGHT);
	}

	if (gp.A.hasPressEvent())
	{
		moveIfAllowed(TetrisBlock::Move::ROTATE_LEFT);
	}

	if (gp.B.hasPressEvent() || gp.North.hasPressEvent())
	{
		moveIfAllowed(TetrisBlock::Move::ROTATE_RIGHT);
	}

	if (gp.South.hasPressEvent())
	{
		moveIfAllowed(TetrisBlock::Move::DOWN);
	}
}

bool MainScreen::moveIfAllowed(TetrisBlock::Move move)
{
	auto copy = _currentBlock;
	copy.makeMove(move);
	if (copy.doesCollide(_field))
	{
		return false;
	}

	_currentBlock.makeMove(move);
	return true;
}

void MainScreen::makeStepIfDue()
{
	if (now() < _tNextStep) { return; }

	_score.scoreStep();
	if (!moveIfAllowed(TetrisBlock::Move::DOWN))
	{
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
