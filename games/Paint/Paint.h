#pragma once

#include <FlipdotConfig.h>
#include <IGame.h>

class Environment;

class Paint : public IGame
{
	public:
		Paint(Environment& env);
		virtual ~Paint();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		Environment& _env;
		int _cursorX = 5;
		int _cursorY = 5;

};
