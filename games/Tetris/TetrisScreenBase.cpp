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
	return _game.getScreens();
}

unsigned TetrisScreenBase::timeSinceEntered()
{
	return _game.timeSinceLastScreenChange();
}

void TetrisScreenBase::setNextScreen(TetrisScreenBase& screen)
{
	_game.setNextScreen(screen);
}

unsigned TetrisScreenBase::now()
{
	return _game.now();
}

TetrisVariables& TetrisScreenBase::getVariables()
{
	return _game.getVariables();
}

bool TetrisScreenBase::isAnyKeyPressed()
{
	return getGamepad().isAnyKeyPressed();
}

bool TetrisScreenBase::wasKeyPressed(GamepadKey key)
{
	return getGamepad().wasKeyPressed(key);
}

bool TetrisScreenBase::wasKeyReleased(GamepadKey key)
{
	return getGamepad().wasKeyReleased(key);
}

bool TetrisScreenBase::wasStartOrSelectPressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_START)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_SELECT);
}

bool TetrisScreenBase::wasRightOrUpPressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_RIGHT)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_UP);
}

bool TetrisScreenBase::wasLeftOrDownPressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_LEFT)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_DOWN);
}
