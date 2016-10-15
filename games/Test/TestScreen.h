#pragma once

#include <IGame.h>
#include <GameScreenBase.h>

class Environment;

class TestScreen: public IGame, public GameScreenBase
{
	public:
		using GameScreenBase::GameScreenBase;
		void init() override;
		void update() override;

	private:
		static const unsigned STEP_INTERVAL = 250;

		unsigned _tNextStep = 0;
		unsigned _pointX = 0;
		unsigned _pointY = 0;

};
