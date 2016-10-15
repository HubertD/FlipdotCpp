#pragma once

class IGame
{
	public:
		virtual ~IGame() {};

		virtual void init() = 0;
		virtual void update() = 0;

	protected:
		IGame() {};

};
