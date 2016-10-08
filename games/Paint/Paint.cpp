#include "Paint.h"

#include <FlipdotGfx.h>
#include <IGamepad.h>

Paint::Paint(FlipdotGfx& gfx)
  : _gfx(gfx)
{
}

Paint::~Paint() {
}

void Paint::init(unsigned ticks)
{
	_gfx.clear();
}

void Paint::update(unsigned ticks)
{
	auto& gamepad = _gfx.getGamepad();

	if (gamepad.wasKeyPressed(GamepadKey::KEY_LEFT))
	{
		_cursorX -= 1;
	}

	if (gamepad.wasKeyPressed(GamepadKey::KEY_RIGHT))
	{
		_cursorX += 1;
	}

	if (gamepad.wasKeyPressed(GamepadKey::KEY_UP))
	{
		_cursorY -= 1;
	}

	if (gamepad.wasKeyPressed(GamepadKey::KEY_DOWN))
	{
		_cursorY += 1;
	}

	gamepad.resetEvents();

	if (_cursorX < 0) { _cursorX = SCREEN_WIDTH-1; }
	if (_cursorX >= SCREEN_WIDTH) { _cursorX = 0; }

	if (_cursorY < 0) { _cursorY = SCREEN_HEIGHT-1; }
	if (_cursorY >= SCREEN_HEIGHT) { _cursorY = 0; }

	_gfx.clear();
	_gfx.drawNumber(SCREEN_WIDTH/2+4, SCREEN_HEIGHT/2-4, 42);
	_gfx.drawNumber(25, 35, 123456, FlipdotColor::BLACK, Orientation::DEG_90);
	_gfx.drawNumber(1,  5, 123456,  FlipdotColor::BLACK, Orientation::DEG_270);
	_gfx.drawText(2, 32, "FNORD");

	_gfx.setPixel(_cursorX, _cursorY, true);

}
