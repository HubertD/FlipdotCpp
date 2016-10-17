#include <GameScreenBase.h>
#include <Environment.h>
#include <Font.h>
#include <Gamepad.h>

GameScreenBase::GameScreenBase(Environment& env)
  : _env(env)
{
}

GameScreenBase::~GameScreenBase()
{
}

Framebuffer& GameScreenBase::getFramebuffer()
{
	return _env.framebuffer;
}

Gamepad& GameScreenBase::getGamepad()
{
	return _env.gamepad;
}

unsigned GameScreenBase::now()
{
	return _env.now;
}

bool GameScreenBase::isAnyKeyPressed()
{
	auto& gp = _env.gamepad;
	return gp.A.isPressed()
		|| gp.B.isPressed()
		|| gp.North.isPressed()
		|| gp.South.isPressed()
		|| gp.West.isPressed()
		|| gp.East.isPressed()
		|| gp.Start.isPressed()
		|| gp.Select.isPressed();
}

bool GameScreenBase::wasAnyKeyPressed()
{
	auto& gp = _env.gamepad;
	return gp.A.hasPressEvent()
		|| gp.B.hasPressEvent()
		|| gp.North.hasPressEvent()
		|| gp.South.hasPressEvent()
		|| gp.West.hasPressEvent()
		|| gp.East.hasPressEvent()
		|| gp.Start.hasPressEvent()
		|| gp.Select.hasPressEvent();
}

bool GameScreenBase::wasContinuePressed()
{
	auto& gp = _env.gamepad;
	return gp.Start.hasPressEvent()
		|| gp.A.hasPressEvent();
}

bool GameScreenBase::wasNextPressed()
{
	auto& gp = _env.gamepad;
	return gp.East.hasPressEvent() || gp.North.hasPressEvent();
}

bool GameScreenBase::wasPreviousPressed()
{
	auto& gp = _env.gamepad;
	return gp.West.hasPressEvent() || gp.South.hasPressEvent();
}

void GameScreenBase::clearScreen()
{
	_env.framebuffer.clear();
}

void GameScreenBase::setPixel(unsigned x, unsigned y, bool value)
{
	_env.framebuffer.setPixel(x, y, value);
}

void GameScreenBase::drawRect(Rect rect, bool value)
{
	_env.framebuffer.drawRect(rect, value);
}

void GameScreenBase::drawChar(unsigned x, unsigned y, char ch, Color color, Orientation orientation)
{
	Font::drawChar(_env.framebuffer, x, y, ch, color, orientation);
}

void GameScreenBase::drawText(unsigned x, unsigned y, char* text,
		Color color, Orientation orientation, int spacing)
{
	Font::drawText(_env.framebuffer, x, y, text, color, orientation, spacing);
}

void GameScreenBase::drawNumber(unsigned x, unsigned y, unsigned number,
		Color color, Orientation orientation, int spacing)
{
	Font::drawNumber(_env.framebuffer, x, y, number, color, orientation, spacing);
}

void GameScreenBase::drawObject(int x, int y, const IDrawable &drawable, bool doInvert)
{
	_env.framebuffer.draw(x, y, drawable, doInvert);
}
