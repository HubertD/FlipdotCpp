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
	_score = 13307;
	_level = getVariables().startLevel;
	_destructedLines = 0;
	_stepInterval = 500;
	_tNextStep = now();

	_field.clear();
	switchToNextBlock();
}

void MainScreen::update()
{
	updateGamepad();
	makeStepIfDue();
	checkRemoveFullRows();
	if (!checkGameOver())
	{
		draw();
	}
}

void MainScreen::updateGamepad()
{
	if (wasKeyPressed(GamepadKey::KEY_RIGHT))
	{
		moveIfAllowed(TetrisBlock::Move::RIGHT);
	}

	if (wasKeyPressed(GamepadKey::KEY_LEFT))
	{
		moveIfAllowed(TetrisBlock::Move::LEFT);
	}

	if (wasKeyPressed(GamepadKey::KEY_A) || wasKeyPressed(GamepadKey::KEY_UP))
	{
		moveIfAllowed(TetrisBlock::Move::ROTATE_RIGHT);
	}

	if (wasKeyPressed(GamepadKey::KEY_B))
	{
		moveIfAllowed(TetrisBlock::Move::ROTATE_LEFT);
	}

	if (wasKeyPressed(GamepadKey::KEY_DOWN))
	{
		moveIfAllowed(TetrisBlock::Move::DOWN);
	}
}

void MainScreen::makeStepIfDue()
{
	if (now() < _tNextStep) { return; }

	if (!moveIfAllowed(TetrisBlock::Move::DOWN))
	{
		_currentBlock.merge(_field);
		switchToNextBlock();
	}

	_tNextStep += _stepInterval;
}


void MainScreen::checkRemoveFullRows()
{
	_field.deleteFullRows();
}

bool MainScreen::checkGameOver()
{
	if (_currentBlock.doesCollide(_field))
	{
		setNextScreen(getScreens().GetReady); /* Game over */
		return true;
	} else {
		return false;
	}
}

bool MainScreen::isMoveAllowed(TetrisBlock::Move move)
{
	auto copy = _currentBlock;
	copy.makeMove(move);
	return !copy.doesCollide(_field);
}

bool MainScreen::moveIfAllowed(TetrisBlock::Move move)
{
	if (isMoveAllowed(move))
	{
		_currentBlock.makeMove(move);
		return true;
	} else {
		return false;
	}
}

void MainScreen::switchToNextBlock()
{
	_currentBlock = _nextBlock;
	_currentBlock.setX((TetrisField::FIELD_WIDTH / 2) - 1);
	_currentBlock.setY(-3);
	_nextBlock = TetrisBlock::createRandomBlock();
}

void MainScreen::draw()
{
	clearScreen();
	drawRect(20, 0, 12, 40, true);
	drawLevel();
	drawScore();
	drawField();
	drawNextBlock();
}

void MainScreen::drawLevel()
{
	drawChar(21, 0, 'L', FlipdotColor::WHITE);
	drawChar(25, 0, ':', FlipdotColor::WHITE);
	drawChar(28, 0, '0'+_level, FlipdotColor::WHITE);
}

void MainScreen::drawScore()
{
	if (_score < 10000) {
		drawNumber(24, 42, _score, FlipdotColor::WHITE, Orientation::DEG_90);
	} else {
		drawNumber(24, 37, _score, FlipdotColor::WHITE, Orientation::DEG_90);
		drawChar(24, 38, 'K', FlipdotColor::WHITE, Orientation::DEG_90);
	}
}

void MainScreen::drawField()
{
	drawObject(FIELD_X, FIELD_Y, _field);
	_currentBlock.draw(getGfx(), FIELD_X, FIELD_Y, 2, 2, FlipdotColor::BLACK);
}

void MainScreen::drawNextBlock()
{
	_nextBlock.draw(getGfx(), NEXT_BLOCK_X, NEXT_BLOCK_Y, TetrisField::POINT_WIDTH, TetrisField::POINT_HEIGHT, FlipdotColor::WHITE);
}
