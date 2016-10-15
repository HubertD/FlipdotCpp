#pragma once

#include "TetrisScreenBase.h"
#include "Screens/LogoScreen.h"
#include "Screens/IdleScreen.h"
#include "Screens/SelectLevelScreen.h"
#include "Screens/GetReadyScreen.h"
#include "Screens/MainScreen.h"
#include "Screens/TryAgainScreen.h"
#include "Screens/NewHighscoreScreen.h"

struct TetrisScreens
{
	TetrisScreenBase Null;
	LogoScreen Logo;
	IdleScreen Idle;
	SelectLevelScreen SelectLevel;
	GetReadyScreen GetReady;
	MainScreen Main;
	TryAgainScreen TryAgain;
	NewHighscoreScreen NewHighscore;

	TetrisScreens(TetrisGame& game)
	  : Null(game),
		Logo(game),
		Idle(game),
		SelectLevel(game),
		GetReady(game),
		Main(game),
		TryAgain(game),
		NewHighscore(game)
	{
	}
};
