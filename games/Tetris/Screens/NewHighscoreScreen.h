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
		static const int BLINK_INTERVAL = 500;

		char _name[NUM_CHARS+1] = {0};
		int _cursorPosition = 0;
		unsigned _tNextBlinkToggle = 0;
		bool _showBlinkingChar = true;

		void draw();
		char getNextChar(char ch);
		char getPreviousChar(char ch);
};
