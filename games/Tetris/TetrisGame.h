#pragma once

#include <IGame.h>
#include "TetrisScreens.h"
#include "TetrisVariables.h"

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

		TetrisScreens &getScreens();
		TetrisVariables &getVariables();
		void setNextScreen(TetrisScreenBase& screen);

		unsigned now();
		unsigned timeSinceLastScreenChange();

	private:
		FlipdotGfx& _gfx;
		IGamepad& _gamepad;
		TetrisScreens _screens;
		TetrisVariables _variables;

		TetrisScreenBase* _lastScreen = &_screens.Null;
		TetrisScreenBase* _currentScreen = &_screens.Null;
		TetrisScreenBase* _nextScreen = &_screens.Logo;

		unsigned _now = 0;
		unsigned _tLastScreenChange = 0;


};
