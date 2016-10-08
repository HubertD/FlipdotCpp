#pragma once

#include <FlipdotConfig.h>
#include <IGame.h>

class FlipdotGfx;

class Paint : public IGame
{
	public:
		Paint(FlipdotGfx& gfx);
		virtual ~Paint();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		FlipdotGfx& _gfx;
		int _cursorX = SCREEN_WIDTH / 2;
		int _cursorY = SCREEN_HEIGHT / 2;

};
