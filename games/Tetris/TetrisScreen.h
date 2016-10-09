#pragma once

#include "TetrisState.h"

#include <FlipdotGfx.h>
#include <IGamepad.h>

class TetrisGame;

class TetrisScreen
{
	protected:
		TetrisGame& _game;
		FlipdotGfx& _gfx;
		IGamepad& _gamepad;

		unsigned _now = 0;
		unsigned _tEntered = 0;
		TetrisState _nextState = TetrisState::IDLE;

		void setNextState(TetrisState state)
		{
			_nextState = state;
		}

	protected:
		virtual void onEnter() {};
		virtual void onUpdate() {};
		virtual void onLeave() {};

	public:
		TetrisScreen(TetrisGame &game);

		virtual ~TetrisScreen();

		void enter(unsigned ticks, TetrisState myState);
		void leave(unsigned ticks);
		TetrisState update(unsigned ticks);
		unsigned timeSinceEntered();
};
