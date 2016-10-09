#include "Tetris.h"

#include <assets/Bitmaps.h>
#include <IGamepad.h>

Tetris::Tetris(FlipdotGfx& gfx)
  : _gfx(gfx), _gamepad(gfx.getGamepad()),
	_logoScreen(gfx),
	_idleScreen(gfx),
	_selectLevelScreen(gfx),
	_currentScreen(&_logoScreen),
	_lastScreen(&_logoScreen)
{
}

Tetris::~Tetris()
{
}

void Tetris::init(unsigned ticks)
{
	_currentState = TetrisState::LOGO;
	_currentScreen = &_logoScreen;
	_currentScreen->enter(ticks, _currentState);
}


void Tetris::update(unsigned ticks)
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

TetrisScreen& Tetris::getScreenForState(TetrisState state)
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
