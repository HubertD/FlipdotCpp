#pragma once

#include <IGame.h>
#include "TetrisScreens.h"

class TetrisGame : public IGame
{
	public:
		TetrisGame(FlipdotGfx& gfx);
		~TetrisGame();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	public:
		FlipdotGfx& getGfx();
		IGamepad& getGamepad();

		void setNextScreen(TetrisScreenBase& screen);
		unsigned timeSinceLastScreenChange();

	private:
		FlipdotGfx& _gfx;
		IGamepad& _gamepad;

		TetrisScreenBase* _lastScreen = &screens.Null;
		TetrisScreenBase* _currentScreen = &screens.Null;
		TetrisScreenBase* _nextScreen = &screens.Logo;

		unsigned _now = 0;
		unsigned _tLastScreenChange = 0;

	public:
		struct Variables
		{
			unsigned startLevel = 1;
		};
		TetrisScreens screens;


};
