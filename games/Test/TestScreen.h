#pragma once

#include <IGame.h>

class TestScreen: public IGame
{
	public:
		TestScreen(IFlipdotGfx& gfx);
		virtual ~TestScreen();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		static const unsigned STEP_INTERVAL = 250;

		IFlipdotGfx& _gfx;

		unsigned _tNextStep = 0;
		unsigned _pointX = 0;
		unsigned _pointY = 0;

};
