#pragma once

#include "../TetrisScreenBase.h"

class TryAgainScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;

		void enter() override;
		void update() override;

	private:
		static const unsigned T_IGNORE_KEYS = 2000;
		static const unsigned T_GOTO_LOGO = 30000;

		void draw();
};
