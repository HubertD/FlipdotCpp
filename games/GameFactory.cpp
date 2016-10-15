/*
 * GameFactory.cpp
 *
 *  Created on: 04.10.2016
 *      Author: hd
 */

#include "GameFactory.h"
#include <Environment.h>

#include <games/Tetris/TetrisGame.h>
#include "Screensaver/Screensaver.h"
#include "Life/GameOfLife.h"
#include "Test/TestScreen.h"
#include "Paint/Paint.h"
#include "Tetris/TetrisGame.h"

IGame* GameFactory::createGame(Game game, Environment& env)
{
	switch (game)
	{
		case Game::TESTSCREEN:
			return new TestScreen(env.gfx);

		case Game::GAME_OF_LIFE:
			return new GameOfLife(env.gfx);

		case Game::PAINT:
			return new Paint(env.gfx);

		case Game::TETRIS:
			return new TetrisGame(env);

		case Game::SCREENSAVER:
		default:
			return new Screensaver(env.gfx);
	}
}

