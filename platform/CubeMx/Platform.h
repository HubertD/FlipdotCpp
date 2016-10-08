#pragma once

#include <IPlatform.h>
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
		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		CubeMxFlipdotDriver _driver;
};

typedef CubeMxPlatform Platform;
