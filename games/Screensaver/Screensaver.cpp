#include "Screensaver.h"

Screensaver::Screensaver(IFlipdotGfx& gfx)
  : _gfx(gfx)
{
}

Screensaver::~Screensaver()
{
}

void Screensaver::init(unsigned ticks)
{
	_tNextStep = ticks + 1000;
	_maxX = _gfx.getScreenWidth() - 1;
	_maxY = _gfx.getScreenHeight() - 1;
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
	_gfx.drawChar( 5, 18, 'X', true);
	_gfx.drawChar(15, 18, 'O', true);
	_gfx.drawChar(25, 18, 'R', true);
	_gfx.setPixel(_ballX, _ballY, true);
}
