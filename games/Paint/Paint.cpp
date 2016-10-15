#include "Paint.h"

#include <Environment.h>
#include <IGamepad.h>
#include <Font.h>
#include <assets/Bitmaps.h>
#include <Framebuffer.h>

Paint::Paint(Environment& env)
  : _env(env)
{
}

Paint::~Paint() {
}

void Paint::init(unsigned ticks)
{
	(void) ticks;
	_env.framebuffer.clear();
}

void Paint::update(unsigned ticks)
{
	(void) ticks;
	auto& gamepad = _env.gamepad;

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
	if (_cursorX >= (int)SCREEN_WIDTH) { _cursorX = 0; }

	if (_cursorY < 0) { _cursorY = SCREEN_HEIGHT-1; }
	if (_cursorY >= (int)SCREEN_HEIGHT) { _cursorY = 0; }

	auto& fb = _env.framebuffer;
	fb.clear();

	Font::drawNumber(fb, SCREEN_WIDTH/2+4, SCREEN_HEIGHT/2-4, 42);
	Font::drawNumber(fb, 25, 35, 123456, Color::BLACK, Orientation::DEG_90);
	Font::drawNumber(fb, 1,  5, 123456,  Color::BLACK, Orientation::DEG_270);
	Font::drawText(fb, 2, 32, (char*)"FNORD");

	fb.setPixel(_cursorX, _cursorY, true);
	fb.draw(0, 0, BytewerkLogo);

}
