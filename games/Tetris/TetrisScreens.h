#pragma once

#include "TetrisScreenBase.h"
#include "Screens/LogoScreen.h"
#include "Screens/IdleScreen.h"
#include "Screens/SelectLevelScreen.h"

struct TetrisScreens
{
	TetrisScreenBase Null;
	LogoScreen Logo;
	IdleScreen Idle;
	SelectLevelScreen SelectLevel;

	TetrisScreens(TetrisGame& game)
	  : Null(game), Logo(game), Idle(game), SelectLevel(game)
	{
	}
};
