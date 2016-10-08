#pragma once

class IGame
{
	public:
		virtual ~IGame() {};

		virtual void init(unsigned ticks) = 0;
		virtual void update(unsigned ticks) = 0;

	protected:
		IGame() {};

};
