#include "Paint.h"

#include <Environment.h>
#include <IGamepad.h>
#include <Font.h>
#include <assets/Bitmaps.h>
#include <Framebuffer.h>

void Paint::init(unsigned ticks)
{
	(void) ticks;
	clearScreen();
}

void Paint::update(unsigned ticks)
{
	(void) ticks;
	auto& gamepad = getGamepad();

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

	clearScreen();

	drawNumber(SCREEN_WIDTH/2+4, SCREEN_HEIGHT/2-4, 42);
	drawNumber(25, 35, 123456, Color::BLACK, Orientation::DEG_90);
	drawNumber(1,  5, 123456,  Color::BLACK, Orientation::DEG_270);
	drawText(2, 32, (char*)"FNORD");

	setPixel(_cursorX, _cursorY, true);
	drawObject(0, 0, BytewerkLogo);

}
