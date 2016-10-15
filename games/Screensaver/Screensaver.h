#pragma once

#include <IGame.h>
#include <GameScreenBase.h>

class Environment;

class Screensaver: public GameScreenBase, public IGame
{
	public:
		using GameScreenBase::GameScreenBase;
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		static const unsigned STEP_INTERVAL = 35;

		unsigned _ballX = 0;
		unsigned _ballY = 0;

		int _speedX = 1;
		int _speedY = 1;

		unsigned _maxX = 0;
		unsigned _maxY = 0;

		unsigned _tNextStep = 0;

		void makeStep();
		void redraw();
};
