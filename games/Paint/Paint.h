#pragma once

#include <FlipdotConfig.h>
#include <IGame.h>
#include <GameScreenBase.h>

class Environment;

class Paint : public GameScreenBase, public IGame
{
	public:
		using GameScreenBase::GameScreenBase;
		void init() override;
		void update() override;

	private:
		int _cursorX = 5;
		int _cursorY = 5;

};
