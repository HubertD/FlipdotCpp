#include "TestScreen.h"

#include <FlipdotConfig.h>
#include <Environment.h>
#include <Framebuffer.h>

void TestScreen::init()
{
	_tNextStep = _env.now + STEP_INTERVAL;
}

void TestScreen::update()
{
	if (_env.now < _tNextStep)
	{
		return;
	}
	_tNextStep = _env.now + STEP_INTERVAL;

	if (++_pointX >= SCREEN_WIDTH)
	{
		_pointX = 0;
	}

	if (++_pointY >= SCREEN_HEIGHT)
	{
		_pointY = 0;
	}

	clearScreen();
	setPixel(_pointX, _pointY, true);

}

