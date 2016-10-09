#pragma once

#include "../TetrisScreen.h"

class SelectLevelScreen : public TetrisScreen
{
	public:
		using TetrisScreen::TetrisScreen;

		void enter() override;
		void update() override;

	private:
		void draw();

};
