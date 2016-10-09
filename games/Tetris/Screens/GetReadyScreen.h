#pragma once

#include "../TetrisScreenBase.h"

class GetReadyScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;

		static const unsigned TIMEOUT = 2000;
		void enter() override;
		void update() override;

};
