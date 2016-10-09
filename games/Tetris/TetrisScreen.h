#pragma once

#include "TetrisState.h"

#include <FlipdotGfx.h>
#include <IGamepad.h>

class TetrisGame;

class TetrisScreen
{

	protected:
		TetrisGame& _game;

		unsigned timeSinceEntered();

	public:
		TetrisScreen(TetrisGame &game);
		TetrisScreen( const TetrisScreen& other ) = delete;
		TetrisScreen& operator=( const TetrisScreen& ) = delete;
		virtual ~TetrisScreen();

		virtual void enter() {};
		virtual void update() {};
		virtual void leave() {};

};
