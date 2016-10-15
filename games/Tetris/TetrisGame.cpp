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
	_now = ticks;
	setNextScreen(_screens.Logo);
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
	_env.gamepad.resetEvents();
}

Environment& TetrisGame::getEnvironment()
{
	return _env;
}

FlipdotFramebuffer& TetrisGame::getFramebuffer()
{
	return _env.framebuffer;
}

IGamepad& TetrisGame::getGamepad()
{
	return _env.gamepad;
}

void TetrisGame::setNextScreen(TetrisScreenBase& screen)
{
	_nextScreen = &screen;
}

unsigned TetrisGame::timeSinceLastScreenChange()
{
	return _now - _tLastScreenChange;
}

unsigned TetrisGame::now()
{
	return _now;
}

TetrisScreens& TetrisGame::getScreens()
{
	return _screens;
}

TetrisVariables& TetrisGame::getVariables()
{
	return _variables;
}
