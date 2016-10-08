#pragma once

#include <IGame.h>

class FlipdotGfx;

class TestScreen: public IGame
{
	public:
		TestScreen(FlipdotGfx& gfx);
		virtual ~TestScreen();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		static const unsigned STEP_INTERVAL = 250;

		FlipdotGfx& _gfx;

		unsigned _tNextStep = 0;
		unsigned _pointX = 0;
		unsigned _pointY = 0;

};
