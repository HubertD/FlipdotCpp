#pragma once

#include <IPlatform.h>
#include <FlipdotFramebuffer.h>

#include "stm32f0xx_hal.h"
#include "CubeMxFlipdotDriver.h"

class CubeMxPlatform : IPlatform
{
	public:
		CubeMxPlatform();

		void init() override;
		void done() override;
		void update() override {};

		IFlipdotDriver &getFlipdotDriver() override;
		IFlipdotFramebuffer &getFramebuffer() override;
		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		CubeMxFlipdotDriver _driver;
		FlipdotFramebuffer _framebuffer;
};

typedef CubeMxPlatform Platform;

