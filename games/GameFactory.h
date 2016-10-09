#pragma once

#include "IGame.h"

class FlipdotGfx;

class GameFactory
{
	public:

		enum class Game {
			TESTSCREEN,
			SCREENSAVER,
			GAME_OF_LIFE,
			PAINT,
			TETRIS,
			_COUNT
		};

		static IGame *createGame(Game game, FlipdotGfx &gfx);

	private:
		GameFactory() {};

};
