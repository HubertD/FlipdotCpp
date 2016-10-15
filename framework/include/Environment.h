#pragma once

class Framebuffer;
class IGamepad;

class Environment
{
	public:
		Framebuffer& framebuffer;
		IGamepad& gamepad;
		unsigned now = 0;

		Environment(Framebuffer& fb, IGamepad& gpad)
		  : framebuffer(fb),
			gamepad(gpad)
		{
		}

		void setCurrentTime(unsigned t)
		{
			now = t;
		}
};
