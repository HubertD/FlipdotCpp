#pragma once

#include "../TetrisScreenBase.h"

class IdleScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;
		void enter() override;
		void update() override;
};
