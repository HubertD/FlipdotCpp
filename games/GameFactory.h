#pragma once

#include "IGame.h"

class IFlipdotGfx;

class GameFactory
{
	public:

		enum class Game {
			TESTSCREEN,
			SCREENSAVER,
			GAME_OF_LIFE,
			_COUNT
		};

		static IGame *createGame(Game game, IFlipdotGfx &gfx);

	private:
		GameFactory() {};

};
