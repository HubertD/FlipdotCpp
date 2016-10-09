#pragma once

#include <FlipdotGfx.h>
#include <IGamepad.h>

class TetrisGame;
class TetrisScreens;
class FlipdotGfx;
class IGamepad;

class TetrisScreenBase
{

	protected:
		FlipdotGfx &getGfx();
		IGamepad &getGamepad();
		TetrisScreens &getScreens();
		unsigned timeSinceEntered();
		void setNextScreen(TetrisScreenBase& screen);

	public:
		TetrisScreenBase(TetrisGame &game);
		TetrisScreenBase( const TetrisScreenBase& other ) = delete;
		TetrisScreenBase& operator=( const TetrisScreenBase& ) = delete;
		virtual ~TetrisScreenBase();

		virtual void enter() {};
		virtual void update() {};
		virtual void leave() {};

	private:
		TetrisGame& _game;

};
