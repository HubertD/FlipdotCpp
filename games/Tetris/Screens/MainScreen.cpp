#include <games/Tetris/Screens/MainScreen.h>
#include <stdlib.h>

#include <games/Tetris/TetrisVariables.h>
#include <games/Tetris/TetrisBlock.h>
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
	_score = 0;
	_scoreBuf = 0;
	_level = getVariables().startLevel;
	_destructedRows = 0;
	_tNextStep = now();
	getVariables().lastScore = 0;

	_field.clear();

	_state = State::RUNNING;
	switchToNextBlock();
	updateLevel();
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
		_field.setInvertFullRows(false);
		_tBlinkNextToggle = 0;

		removeFullRows();
		_state = State::RUNNING;
		_tNextStep = now() + _stepInterval;

	} else {
		_tBlinkNextToggle = now() + DELETED_ROWS_BLINK_INTERVAL;
		_field.setInvertFullRows((_blinkTogglesRemaining % 2) == 0);
	}
}

void MainScreen::checkCommands()
{
	if (wasKeyPressed(GamepadKey::KEY_RIGHT))
	{
		moveIfAllowed(TetrisBlock::Move::RIGHT);
	}

	if (wasKeyPressed(GamepadKey::KEY_LEFT))
	{
		moveIfAllowed(TetrisBlock::Move::LEFT);
	}

	if (wasKeyPressed(GamepadKey::KEY_A))
	{
		moveIfAllowed(TetrisBlock::Move::ROTATE_LEFT);
	}

	if (wasKeyPressed(GamepadKey::KEY_B) || wasKeyPressed(GamepadKey::KEY_UP))
	{
		moveIfAllowed(TetrisBlock::Move::ROTATE_RIGHT);
	}

	if (wasKeyPressed(GamepadKey::KEY_DOWN))
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

	_scoreBuf += (_level+1) * POINTS_PER_STEP_FACTOR;
	if (!moveIfAllowed(TetrisBlock::Move::DOWN))
	{
		_currentBlock.merge(_field);
		_score += _scoreBuf;
		_scoreBuf = 0;
		switchToNextBlock();
	}

	_tNextStep = now() + _stepInterval;
}

void MainScreen::switchToNextBlock()
{
	_currentBlock = _nextBlock;
	_currentBlock.setX((TetrisField::FIELD_WIDTH / 2) - 1);
	_currentBlock.setY(-3);
	_nextBlock = TetrisBlock::createRandomBlock();
}

void MainScreen::removeFullRows()
{
	int deletedRows = _field.deleteFullRows();

	if (deletedRows>0)
	{
		_destructedRows += deletedRows;
		_score += calcPointsForDeletedRows(deletedRows);
		updateLevel();
	}
}

void MainScreen::checkGameOver()
{
	if (_currentBlock.doesCollide(_field))
	{
		getVariables().lastScore = _score;
		_state = State::GAME_OVER;
		_tGameOverWait = now() + WAIT_AFTER_GAME_OVER;
	}
}

void MainScreen::draw()
{
	clearScreen();

	drawRect(20, 0, 12, 40, true);

	drawChar(LEVEL_X,   LEVEL_Y, 'L', Color::WHITE);
	drawChar(LEVEL_X+3, LEVEL_Y, ':', Color::WHITE);
	drawChar(LEVEL_X+7, LEVEL_Y, '0'+_level, Color::WHITE);

	if (_score < SCORE_SHOW_K)
	{
		drawNumber(SCORE_X, SCORE_Y, _score, Color::WHITE, Orientation::DEG_90);
	} else {
		drawNumber(SCORE_X, SCORE_Y-5, _score/1000, Color::WHITE, Orientation::DEG_90);
		drawChar(SCORE_X, SCORE_Y-4, 'K', Color::WHITE, Orientation::DEG_90);
	}

	_nextBlock.draw(getFramebuffer(), NEXT_BLOCK_X, NEXT_BLOCK_Y, TetrisField::POINT_WIDTH, TetrisField::POINT_HEIGHT, Color::WHITE);

	drawObject(FIELD_X, FIELD_Y, _field);
	_currentBlock.draw(getFramebuffer(), FIELD_X, FIELD_Y, 2, 2, Color::BLACK);
}

int MainScreen::calcPointsForDeletedRows(int deletedRows)
{
	int factor = 0;
	switch (deletedRows)
	{
		case 1:
			factor = POINTS_1_ROW_FACTOR;
			break;
		case 2:
			factor = POINTS_2_ROWS_FACTOR;
			break;
		case 3:
			factor = POINTS_3_ROWS_FACTOR;
			break;
		case 4:
			factor = POINTS_4_ROWS_FACTOR;
			break;
	}
	return (_level+1) * factor;
}

void MainScreen::updateLevel()
{
	_level = (_destructedRows / ROWS_FOR_LEVEL_UP) + getVariables().startLevel;

	if(_level > MAX_LEVEL)
	{
	  _level = MAX_LEVEL;
	}

	_stepInterval = STEP_INTERVAL_LEVEL_0 + (_level * STEP_INTERVAL_LEVEL_DELTA);
}
