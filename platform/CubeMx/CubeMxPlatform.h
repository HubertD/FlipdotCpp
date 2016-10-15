#pragma once

#include <IPlatform.h>
#include <Framebuffer.h>
#include <Gamepad.h>
#include "CubeMxFlipdotDriver.h"

class CubeMxPlatform : IPlatform
{
	public:
		CubeMxPlatform();

		void init() override;
		void done() override;
		void update() override;

		Framebuffer& getFramebuffer() override;
		Gamepad& getGamepad() override;

		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		CubeMxFlipdotDriver _driver;
		Framebuffer _framebuffer;
		Gamepad _gamepad;

		uint8_t getNESbyte();
		void sendNESlatch();
		void sendNESclock();
		bool getNESbit();
};

