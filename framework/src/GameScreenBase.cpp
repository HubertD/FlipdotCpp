#include <GameScreenBase.h>
#include <Environment.h>

GameScreenBase::GameScreenBase(Environment& env)
  : _env(env)
{
}

GameScreenBase::~GameScreenBase()
{
}

FlipdotGfx& GameScreenBase::getGfx()
{
	return _env.gfx;
}

IGamepad& GameScreenBase::getGamepad()
{
	return _env.gamepad;
}

unsigned GameScreenBase::now()
{
	return _env.now;
}

bool GameScreenBase::isAnyKeyPressed()
{
	return getGamepad().isAnyKeyPressed();
}

bool GameScreenBase::wasAnyKeyPressed()
{
	return getGamepad().wasAnyKeyPressed();
}

bool GameScreenBase::wasKeyPressed(GamepadKey key)
{
	return getGamepad().wasKeyPressed(key);
}

bool GameScreenBase::wasKeyReleased(GamepadKey key)
{
	return getGamepad().wasKeyReleased(key);
}

bool GameScreenBase::wasContinuePressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_START)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_A);
}

bool GameScreenBase::wasNextPressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_RIGHT)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_UP);
}

bool GameScreenBase::wasPreviousPressed()
{
	return getGamepad().wasKeyPressed(GamepadKey::KEY_LEFT)
		   || getGamepad().wasKeyPressed(GamepadKey::KEY_DOWN);
}

void GameScreenBase::clearScreen()
{
	_env.gfx.clear();
}

void GameScreenBase::setPixel(unsigned x, unsigned y, bool value)
{
	_env.gfx.setPixel(x, y, value);
}

void GameScreenBase::drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value)
{
	_env.gfx.drawRect(x, y, dx, dy, value);
}

void GameScreenBase::drawChar(unsigned x, unsigned y, char ch, FlipdotColor color, Orientation orientation)
{
	_env.gfx.drawChar(x, y, ch, color, orientation);
}

void GameScreenBase::drawText(unsigned x, unsigned y, char* text,
		FlipdotColor color, Orientation orientation, int spacing)
{
	_env.gfx.drawText(x, y, text, color, orientation, spacing);
}

void GameScreenBase::drawNumber(unsigned x, unsigned y, unsigned number,
		FlipdotColor color, Orientation orientation, int spacing)
{
	_env.gfx.drawNumber(x, y, number, color, orientation, spacing);
}

void GameScreenBase::drawObject(int x, int y, const IDrawable &drawable, bool doInvert)
{
	_env.gfx.draw(x, y, drawable, doInvert);
}
