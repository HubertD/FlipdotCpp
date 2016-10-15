#pragma once

#include <IGame.h>

class Environment;

class TestScreen: public IGame
{
	public:
		TestScreen(Environment& env);
		virtual ~TestScreen();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		static const unsigned STEP_INTERVAL = 250;

		Environment& _env;

		unsigned _tNextStep = 0;
		unsigned _pointX = 0;
		unsigned _pointY = 0;

};
