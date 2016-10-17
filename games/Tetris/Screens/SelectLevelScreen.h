#pragma once

#include <games/Tetris/TetrisScreenBase.h>

class SelectLevelScreen : public TetrisScreenBase
{
	public:
		using TetrisScreenBase::TetrisScreenBase;
		void enter() override;
		void update() override;

	private:
		static const unsigned IDLE_TIMEOUT_MS = 15000;
		static const int MIN_LEVEL = 0;
		static const int MAX_LEVEL = 9;

		unsigned _tIdleSince = 0;

		void draw();
		void changeStartLevel(int delta);
		void resetIdleTime();
		bool isIdleTimeout();

};
