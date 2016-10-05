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
	_tNextStep = ticks + 2000;
}

void TestScreen::update(unsigned ticks)
{
	if (ticks < _tNextStep)
	{
		return;
	}
	_tNextStep = ticks + STEP_INTERVAL;


	if (++_pointX >= _gfx.getScreenWidth())
	{
		_pointX = 0;
		if (++_pointY >= _gfx.getScreenHeight())
		{
			_pointY = 0;
		}
	}

	_gfx.clear();
	_gfx.setPixel(_pointX, _pointY, true);


}

