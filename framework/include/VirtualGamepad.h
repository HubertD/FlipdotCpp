#pragma once

#include <stdint.h>
#include "IGamepad.h"

class VirtualGamepad : public IGamepad
{
	public:
		void init() override {};
		void update(unsigned ticks) override;

		bool isKeyPressed(GamepadKey key) override;
		bool isAnyKeyPressed() override;
		bool wasKeyPressed(GamepadKey key) override;
		bool wasKeyReleased(GamepadKey key) override;
		void resetEvents() override;

		void injectKeyPress(GamepadKey key);
		void injectKeyRelease(GamepadKey key);

	private:
		uint32_t _currentStatus = 0;
		uint32_t _lastStatus = 0;

		bool keyStatus(GamepadKey key, uint32_t status);
};
