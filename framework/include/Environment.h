#pragma once

class FlipdotFramebuffer;
class IGamepad;

class Environment
{
	public:
		FlipdotFramebuffer& framebuffer;
		IGamepad& gamepad;
		unsigned now = 0;

		Environment(FlipdotFramebuffer& fb, IGamepad& gpad)
		  : framebuffer(fb),
			gamepad(gpad)
		{
		}

		void setCurrentTime(unsigned t)
		{
			now = t;
		}
};
