#include "Screensaver.h"

#include <FlipdotConfig.h>
#include <FlipdotGfx.h>

Screensaver::Screensaver(FlipdotGfx& gfx)
  : _gfx(gfx)
{
}

Screensaver::~Screensaver()
{
}

void Screensaver::init(unsigned ticks)
{
	_tNextStep = ticks + 1000;
	_maxX = SCREEN_WIDTH - 1;
	_maxY = SCREEN_HEIGHT - 1;
}

void Screensaver::update(unsigned ticks)
{
	if (ticks >= _tNextStep)
	{
		makeStep();
		redraw();
		_tNextStep = ticks + STEP_INTERVAL;
	}
}

void Screensaver::makeStep()
{
	_ballX = (_ballX + _speedX);
	_ballY = (_ballY + _speedY);

	if ((_ballX>=_maxX) || (_ballX<=0)) { _speedX = -_speedX; }
	if ((_ballY>=_maxY) || (_ballY<=0)) { _speedY = -_speedY; }
}

void Screensaver::redraw()
{
	_gfx.clear();
	_gfx.drawChar( 5, 18, 'X');
	_gfx.drawChar(15, 18, 'O');
	_gfx.drawChar(25, 18, 'R');
	_gfx.setPixel(_ballX, _ballY, true);
}
