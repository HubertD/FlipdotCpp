#pragma once

#include <Framebuffer.h>
#include <IPlatform.h>
#include <Gamepad.h>
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

		Framebuffer &getFramebuffer() override;
		Gamepad& getGamepad() override;

		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		static constexpr unsigned UTICKS_PER_UPDATE = 10;

		VCDFlipdotDriver _driver;
		Framebuffer _framebuffer;
		Gamepad _gamepad;

		unsigned _uticks = 0;
		int _uticksQuit = -1;
};

