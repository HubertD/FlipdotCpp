#pragma once

#include "TetrisState.h"

#include <FlipdotGfx.h>
#include <IGamepad.h>

class TetrisScreen
{
	protected:
		FlipdotGfx &_gfx;
		IGamepad &_gamepad;

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
		TetrisScreen(FlipdotGfx& gfx)
		  : _gfx(gfx), _gamepad(gfx.getGamepad())
		{
		}

		virtual ~TetrisScreen()
		{
		}

		void enter(unsigned ticks, TetrisState myState)
		{
			_nextState = myState;
			_tEntered = ticks;
			_now = ticks;
			onEnter();
		}

		void leave(unsigned ticks)
		{
			_now = ticks;
			onLeave();
		}

		TetrisState update(unsigned ticks)
		{
			_now = ticks;
			onUpdate();
			return _nextState;
		}

		unsigned timeSinceEntered()
		{
			return _now - _tEntered;
		}

};
