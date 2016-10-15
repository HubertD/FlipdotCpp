#pragma once

class Framebuffer;
class Gamepad;

class Environment
{
	public:
		Framebuffer& framebuffer;
		Gamepad& gamepad;
		unsigned now = 0;

		Environment(Framebuffer& fb, Gamepad& gpad)
		  : framebuffer(fb),
			gamepad(gpad)
		{
		}

		void setCurrentTime(unsigned t)
		{
			now = t;
		}
};
