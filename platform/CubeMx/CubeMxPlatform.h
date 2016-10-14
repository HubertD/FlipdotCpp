#pragma once

#include <IPlatform.h>
#include <FlipdotFramebuffer.h>
#include <VirtualGamepad.h>
#include "CubeMxFlipdotDriver.h"

class CubeMxPlatform : IPlatform
{
	public:
		CubeMxPlatform();

		void init() override;
		void done() override;
		void update() override;

		FlipdotFramebuffer& getFramebuffer() override;
		IGamepad& getGamepad() override;

		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		CubeMxFlipdotDriver _driver;
		FlipdotFramebuffer _framebuffer;
		VirtualGamepad _gamepad;

		uint8_t getNESbyte();
		void sendNESlatch();
		void sendNESclock();
		bool getNESbit();
};

