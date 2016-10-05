/*
 * TestScreen.cpp
 *
 *  Created on: 05.10.2016
 *      Author: hd
 */

#include "TestScreen.h"

TestScreen::TestScreen(IFlipdotGfx& gfx)
  : _gfx(gfx)
{
}

TestScreen::~TestScreen()
{
}

void TestScreen::init(unsigned ticks)
{
	_tNextStep = ticks + 1000;
}

void TestScreen::update(unsigned ticks)
{
	if (ticks < _tNextStep)
	{
		return;
	}
	_tNextStep = ticks + STEP_INTERVAL;


	{
		_pointX = 0;
		if (++_pointY >= 40)
		{
			_pointY = 0;
		}
	}

	_gfx.clear();

	_gfx.setPixel(0, _pointY, true);
	_gfx.setPixel(15, _pointY, true);
	_gfx.setPixel(16, _pointY, true);
	_gfx.setPixel(31, _pointY, true);
//	_gfx.setPixel(16, _pointY, true);


}

