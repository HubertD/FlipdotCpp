#pragma once

#include <games/Tetris/TetrisScreenBase.h>

class IdleScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;

		void enter();
		void update();

};
