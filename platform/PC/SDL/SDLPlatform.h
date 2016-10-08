#pragma once

#include <IPlatform.h>

#include <SDL2/SDL.h>
#include "SDLFlipdotDriver.h"

class SDLPlatform : IPlatform
{
	public:
		SDLPlatform();

		void init() override;
		void done() override;
		void update() override {};

		IFlipdotDriver &getFlipdotDriver() override;
		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		SDLFlipdotDriver *_driver = nullptr;
		SDL_Window *_window = nullptr;
};

