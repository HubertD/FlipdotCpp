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

	public:
		FlipdotGfx& getGfx();

	private:

		TetrisState _lastState = TetrisState::LOGO;
		TetrisState _currentState = TetrisState::LOGO;

		FlipdotGfx& _gfx;
		IGamepad& _gamepad;

		LogoScreen _logoScreen;
		IdleScreen _idleScreen;
		SelectLevelScreen _selectLevelScreen;

		TetrisScreen *_currentScreen;
		TetrisScreen *_lastScreen;

		TetrisScreen& getScreenForState(TetrisState state);

};
