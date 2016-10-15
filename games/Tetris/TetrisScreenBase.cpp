#include "TetrisScreenBase.h"
#include "TetrisGame.h"

TetrisScreenBase::TetrisScreenBase(TetrisGame& game)
  : GameScreenBase(game.getEnvironment()), _game(game)
{
}

TetrisScreenBase::~TetrisScreenBase()
{
}

TetrisScreens& TetrisScreenBase::getScreens()
{
	return _game.getScreens();
}

TetrisVariables& TetrisScreenBase::getVariables()
{
	return _game.getVariables();
}

unsigned TetrisScreenBase::timeSinceEntered()
{
	return _game.timeSinceLastScreenChange();
}

void TetrisScreenBase::setNextScreen(TetrisScreenBase& screen)
{
	_game.setNextScreen(screen);
}

