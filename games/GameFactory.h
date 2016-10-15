#pragma once

#include "IGame.h"

class Environment;

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

		static IGame *createGame(Game game, Environment& env);

	private:
		GameFactory() {};

};
