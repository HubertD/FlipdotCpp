#include "TetrisGame.h"

TetrisGame::TetrisGame(FlipdotGfx& gfx)
  : _gfx(gfx), _gamepad(gfx.getGamepad()),
	_logoScreen(*this),
	_idleScreen(*this),
	_selectLevelScreen(*this),
	_currentScreen(&_logoScreen),
	_lastScreen(&_logoScreen)
{
}

TetrisGame::~TetrisGame()
{
}

void TetrisGame::init(unsigned ticks)
{
	_currentState = TetrisState::LOGO;
	_currentScreen = &_logoScreen;
	_currentScreen->enter(ticks, _currentState);
}


void TetrisGame::update(unsigned ticks)
{
	TetrisState nextState = _currentScreen->update(ticks);
	if (nextState != _currentState)
	{
		_currentScreen->leave(ticks);
		_lastScreen = _currentScreen;
		_lastState = _currentState;
		_currentState = nextState;
		_currentScreen = &getScreenForState(_currentState);
		_currentScreen->enter(ticks, _currentState);
	}
}

TetrisScreen& TetrisGame::getScreenForState(TetrisState state)
{
	switch (state)
	{
		case TetrisState::IDLE:
			return _idleScreen;

		case TetrisState::SELECT_LEVEL:
			return _selectLevelScreen;

		case TetrisState::LOGO:
		default:
			return _logoScreen;
	}
}

FlipdotGfx& TetrisGame::getGfx()
{
	return _gfx;
}
