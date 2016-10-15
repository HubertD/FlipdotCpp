#pragma once

#include <IGamepad.h>
#include <GameScreenBase.h>

class TetrisGame;
class TetrisScreens;
class TetrisVariables;

class TetrisScreenBase : public GameScreenBase
{

	protected:
		TetrisScreens &getScreens();
		TetrisVariables &getVariables();

	public:
		TetrisScreenBase(TetrisGame &game);
		~TetrisScreenBase() override;

		void enter() override {};
		void update() override {};
		void leave() override {};

		unsigned timeSinceEntered();
		void setNextScreen(TetrisScreenBase& screen);

	private:
		TetrisGame& _game;

};
