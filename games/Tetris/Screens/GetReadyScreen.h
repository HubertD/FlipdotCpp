#pragma once

#include "../TetrisScreenBase.h"

class GetReadyScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;
		void enter() override;
		void update() override;

	private:
		static constexpr unsigned T_SHOW_MIN  = 500;
		static const unsigned TIMEOUT = 2000;
};
