#include "TetrisGame.h"
#include <Environment.h>

TetrisGame::TetrisGame(Environment& env)
  : _env(env),
	_screens(*this),
	_variables()
{
}

TetrisGame::~TetrisGame()
{
}

void TetrisGame::init(unsigned ticks)
{
	(void) ticks;
	setNextScreen(_screens.Logo);
}

void TetrisGame::update(unsigned ticks)
{
	(void) ticks;
	if (_nextScreen != _currentScreen)
	{
		_currentScreen->leave();
		_lastScreen = _currentScreen;
		_currentScreen = _nextScreen;
		_tLastScreenChange = ticks;
		_currentScreen->enter();
	}

	_currentScreen->update();
	_env.gamepad.resetEvents();
}

Environment& TetrisGame::getEnvironment()
{
	return _env;
}

void TetrisGame::setNextScreen(TetrisScreenBase& screen)
{
	_nextScreen = &screen;
}

unsigned TetrisGame::timeSinceLastScreenChange()
{
	return _env.now - _tLastScreenChange;
}

TetrisScreens& TetrisGame::getScreens()
{
	return _screens;
}

TetrisVariables& TetrisGame::getVariables()
{
	return _variables;
}
