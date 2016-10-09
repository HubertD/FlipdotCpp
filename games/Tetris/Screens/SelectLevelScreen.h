#pragma once

#include <games/Tetris/TetrisScreenBase.h>

class SelectLevelScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;

		void enter() override;
		void update() override;

	private:
		void draw();

};
