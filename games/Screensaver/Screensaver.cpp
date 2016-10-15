#include "Screensaver.h"

#include <FlipdotConfig.h>
#include <Environment.h>
#include <FlipdotFramebuffer.h>
#include <Font.h>

Screensaver::Screensaver(Environment& env)
  : _env(env)
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
	auto& fb = _env.framebuffer;
	fb.clear();
	Font::drawChar(fb, 5, 18, 'X');
	Font::drawChar(fb, 15, 18, 'O');
	Font::drawChar(fb, 25, 18, 'R');
	fb.setPixel(_ballX, _ballY, true);
}
