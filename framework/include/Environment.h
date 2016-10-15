#pragma once

class FlipdotGfx;
class IGamepad;

class Environment
{
	public:
		FlipdotGfx& gfx;
		IGamepad& gamepad;
		unsigned now = 0;

		Environment(FlipdotGfx& aGfx, IGamepad& aGamepad)
		  : gfx(aGfx),
			gamepad(aGamepad)
		{
		}

		void setCurrentTime(unsigned t)
		{
			now = t;
		}
};
