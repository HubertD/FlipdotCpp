#pragma once

#include "../TetrisScreenBase.h"

class NewHighscoreScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;
		void enter() override;
		void update() override;

	private:
		static const int NUM_CHARS = 3;

		char _name[NUM_CHARS] = {0};
		int _cursorPosition = 0;

		void draw();
};
