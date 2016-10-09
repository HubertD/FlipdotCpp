#include "TetrisScreenBase.h"
#include "TetrisGame.h"

TetrisScreenBase::TetrisScreenBase(TetrisGame& game)
  : _game(game)
{
}

TetrisScreenBase::~TetrisScreenBase()
{
}

FlipdotGfx& TetrisScreenBase::getGfx()
{
	return _game.getGfx();
}

IGamepad& TetrisScreenBase::getGamepad()
{
	return _game.getGamepad();
}

TetrisScreens& TetrisScreenBase::getScreens()
{
	return _game.screens;
}

unsigned TetrisScreenBase::timeSinceEntered()
{
	return _game.timeSinceLastScreenChange();
}

void TetrisScreenBase::setNextScreen(TetrisScreenBase& screen)
{
	_game.setNextScreen(screen);
}

