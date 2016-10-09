#include "TetrisScreen.h"

#include "TetrisGame.h"

TetrisScreen::TetrisScreen(TetrisGame& game)
  : _game(game), _gfx(game.getGfx()), _gamepad(_gfx.getGamepad())
{
}

TetrisScreen::~TetrisScreen()
{
}

void TetrisScreen::enter(unsigned ticks, TetrisState myState)
{
	_nextState = myState;
	_tEntered = ticks;
	_now = ticks;
	onEnter();
}

void TetrisScreen::leave(unsigned ticks)
{
	_now = ticks;
	onLeave();
}

TetrisState TetrisScreen::update(unsigned ticks)
{
	_now = ticks;
	onUpdate();
	return _nextState;
}

unsigned TetrisScreen::timeSinceEntered()
{
	return _now - _tEntered;
}
