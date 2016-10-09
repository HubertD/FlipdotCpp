#pragma once

#include <FlipdotGfx.h>
#include <IGamepad.h>

class TetrisGame;
class TetrisScreens;
class TetrisVariables;
class FlipdotGfx;
class IGamepad;

class TetrisScreenBase
{

	protected:
		unsigned now();
		FlipdotGfx &getGfx();
		IGamepad &getGamepad();
		TetrisScreens &getScreens();
		TetrisVariables &getVariables();
		unsigned timeSinceEntered();
		void setNextScreen(TetrisScreenBase& screen);

		bool isAnyKeyPressed();
		bool wasKeyPressed(GamepadKey key);
		bool wasKeyReleased(GamepadKey key);
		bool wasStartOrSelectPressed();
		bool wasRightOrUpPressed();
		bool wasLeftOrDownPressed();

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
