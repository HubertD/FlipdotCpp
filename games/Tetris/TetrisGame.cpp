#include "TetrisGame.h"

TetrisGame::TetrisGame(FlipdotGfx& gfx)
  : _gfx(gfx),
	_gamepad(gfx.getGamepad()),
	screens(*this)
{
}

TetrisGame::~TetrisGame()
{
}

void TetrisGame::init(unsigned ticks)
{
	_now = ticks;
	setNextScreen(screens.Logo);
}

void TetrisGame::update(unsigned ticks)
{
	_now = ticks;
	if (_nextScreen != _currentScreen)
	{
		_currentScreen->leave();
		_lastScreen = _currentScreen;
		_currentScreen = _nextScreen;
		_tLastScreenChange = ticks;
		_currentScreen->enter();
	}

	_currentScreen->update();
}

FlipdotGfx& TetrisGame::getGfx()
{
	return _gfx;
}

IGamepad& TetrisGame::getGamepad()
{
	return _gfx.getGamepad();
}

void TetrisGame::setNextScreen(TetrisScreenBase& screen)
{
	_nextScreen = &screen;
}

unsigned TetrisGame::timeSinceLastScreenChange()
{
	return _now - _tLastScreenChange;
}
