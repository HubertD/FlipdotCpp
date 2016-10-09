#pragma once

#include "../TetrisScreen.h"

class IdleScreen : public TetrisScreen
{
	public:
		using TetrisScreen::TetrisScreen;

		void enter();
		void update();

};
