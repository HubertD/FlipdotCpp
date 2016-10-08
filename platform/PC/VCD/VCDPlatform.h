#pragma once

#include <IPlatform.h>
#include <FlipdotFramebuffer.h>
#include <VirtualGamepad.h>
#include "VCDFlipdotDriver.h"

class VCDPlatform : IPlatform
{
	public:
		VCDPlatform();

		void init() override;
		void done() override;
		void update() override;

		void incrementUTicks(int increment);
		unsigned getUTicks();
		void setQuitUTicks(int uticks);

		FlipdotFramebuffer &getFramebuffer() override;
		IGamepad& getGamepad() override;

		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		static constexpr unsigned UTICKS_PER_UPDATE = 10;

		VCDFlipdotDriver _driver;
		FlipdotFramebuffer _framebuffer;
		VirtualGamepad _gamepad;

		unsigned _uticks = 0;
		int _uticksQuit = -1;
};

