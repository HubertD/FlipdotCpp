#pragma once

#include <IPlatform.h>
#include <Framebuffer.h>
#include <Gamepad.h>
#include "STM32F4FlipdotDriver.h"

class STM32F4Platform : IPlatform
{
	public:
		STM32F4Platform();

		void init() override;
		void done() override;
		void update() override;

		Framebuffer& getFramebuffer() override;
		Gamepad& getGamepad() override;

		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		STM32F4FlipdotDriver _driver;
		Framebuffer _framebuffer;
		Gamepad _gamepad;

		uint8_t getNESbyte();
		void sendNESlatch();
		void sendNESclock();
		bool getNESbit();
};

