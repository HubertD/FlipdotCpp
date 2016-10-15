#pragma once

#include <IGame.h>
#include "TetrisScreens.h"
#include "TetrisVariables.h"

class Environment;

class TetrisGame : public IGame
{
	public:
		TetrisGame(Environment& env);
		~TetrisGame();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	public:
		Environment& getEnvironment();
		Framebuffer& getFramebuffer();
		IGamepad& getGamepad();

		TetrisScreens &getScreens();
		TetrisVariables &getVariables();
		void setNextScreen(TetrisScreenBase& screen);

		unsigned now();
		unsigned timeSinceLastScreenChange();

	private:
		Environment& _env;
		TetrisScreens _screens;
		TetrisVariables _variables;

		TetrisScreenBase* _lastScreen = &_screens.Null;
		TetrisScreenBase* _currentScreen = &_screens.Null;
		TetrisScreenBase* _nextScreen = &_screens.Logo;

		unsigned _now = 0;
		unsigned _tLastScreenChange = 0;


};
