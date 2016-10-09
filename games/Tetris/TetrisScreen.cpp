#include "TetrisScreen.h"

#include "TetrisGame.h"

TetrisScreen::TetrisScreen(TetrisGame& game)
  : _game(game)
{
}

TetrisScreen::~TetrisScreen()
{
}

unsigned TetrisScreen::timeSinceEntered()
{
	return _game.timeSinceLastScreenChange();
}
