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

bool TetrisScreenBase::wasContinuePressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_START)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_SELECT);
}

bool TetrisScreenBase::wasNextPressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_RIGHT)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_UP);
}

bool TetrisScreenBase::wasPreviousPressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_LEFT)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_DOWN);
}

void TetrisScreenBase::clearScreen()
{
	_game.getGfx().clear();
}

void TetrisScreenBase::setPixel(unsigned x, unsigned y, bool value)
{
	_game.getGfx().setPixel(x, y, value);
}

void TetrisScreenBase::drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value)
{
	_game.getGfx().drawRect(x, y, dx, dy, value);
}

void TetrisScreenBase::drawChar(unsigned x, unsigned y, char ch, FlipdotColor color, Orientation orientation)
{
	_game.getGfx().drawChar(x, y, ch, color, orientation);
}

void TetrisScreenBase::drawText(unsigned x, unsigned y, char* text,
		FlipdotColor color, Orientation orientation, int spacing)
{
	_game.getGfx().drawText(x, y, text, color, orientation, spacing);
}

void TetrisScreenBase::drawNumber(unsigned x, unsigned y, unsigned number,
		FlipdotColor color, Orientation orientation, int spacing)
{
	_game.getGfx().drawNumber(x, y, number, color, orientation, spacing);
}

void TetrisScreenBase::drawObject(int x, int y, const IDrawable &drawable, bool doInvert)
{
	_game.getGfx().draw(x, y, drawable, doInvert);
}
