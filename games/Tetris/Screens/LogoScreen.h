#pragma once

#include "../TetrisScreen.h"

class LogoScreen : public TetrisScreen
{
	public:
		using TetrisScreen::TetrisScreen;
		void enter() override;
		void update() override;

	private:
		static constexpr unsigned T_LOGO_MIN  = 1000;
		static constexpr unsigned T_LOGO_IDLE = 10000;

};
