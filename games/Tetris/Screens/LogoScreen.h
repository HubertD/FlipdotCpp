#pragma once

#include <games/Tetris/TetrisScreenBase.h>

class LogoScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;
		void enter() override;
		void update() override;

	private:
		static constexpr unsigned T_LOGO_MIN  = 1000;
		static constexpr unsigned T_LOGO_IDLE = 10000;

};
