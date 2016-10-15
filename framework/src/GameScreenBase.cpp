#include <GameScreenBase.h>
#include <Environment.h>
#include <Font.h>

GameScreenBase::GameScreenBase(Environment& env)
  : _env(env)
{
}

GameScreenBase::~GameScreenBase()
{
}

FlipdotFramebuffer& GameScreenBase::getFramebuffer()
{
	return _env.framebuffer;
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
	_env.framebuffer.clear();
}

void GameScreenBase::setPixel(unsigned x, unsigned y, bool value)
{
	_env.framebuffer.setPixel(x, y, value);
}

void GameScreenBase::drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value)
{
	_env.framebuffer.drawRect(x, y, dx, dy, value);
}

void GameScreenBase::drawChar(unsigned x, unsigned y, char ch, FlipdotColor color, Orientation orientation)
{
	Font::drawChar(_env.framebuffer, x, y, ch, color, orientation);
}

void GameScreenBase::drawText(unsigned x, unsigned y, char* text,
		FlipdotColor color, Orientation orientation, int spacing)
{
	Font::drawText(_env.framebuffer, x, y, text, color, orientation, spacing);
}

void GameScreenBase::drawNumber(unsigned x, unsigned y, unsigned number,
		FlipdotColor color, Orientation orientation, int spacing)
{
	Font::drawNumber(_env.framebuffer, x, y, number, color, orientation, spacing);
}

void GameScreenBase::drawObject(int x, int y, const IDrawable &drawable, bool doInvert)
{
	_env.framebuffer.draw(x, y, drawable, doInvert);
}
