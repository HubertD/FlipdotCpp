#pragma once

#include <IGame.h>

#include "TetrisState.h"
#include "TetrisScreen.h"
#include "Screens/LogoScreen.h"
#include "Screens/IdleScreen.h"
#include "Screens/SelectLevelScreen.h"

class TetrisGame : public IGame
{
	public:
		TetrisGame(FlipdotGfx& gfx);
		~TetrisGame();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		FlipdotGfx& _gfx;
		IGamepad& _gamepad;

		TetrisScreen* _lastScreen = &screens.Null;
		TetrisScreen* _currentScreen = &screens.Null;
		TetrisScreen* _nextScreen = &screens.Logo;

		unsigned _now = 0;
		unsigned _tLastScreenChange = 0;

	public:
		FlipdotGfx& gfx();
		IGamepad& gamepad();

		void setNextScreen(TetrisScreen& screen);
		unsigned timeSinceLastScreenChange();

		struct Screens {
			TetrisScreen Null;
			LogoScreen Logo;
			IdleScreen Idle;
			SelectLevelScreen SelectLevel;

			Screens(TetrisGame& game)
			  : Null(game), Logo(game), Idle(game), SelectLevel(game)
			{
			}
		};

		Screens screens;

};
