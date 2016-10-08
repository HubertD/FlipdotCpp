#pragma once

#include <IPlatform.h>

#include <SDL2/SDL.h>
#include "SDL/SDLFlipdotDriver.h"

class PCPlatform : IPlatform
{
	public:
		PCPlatform();

		void init() override;
		void done() override;

		IFlipdotDriver &getFlipdotDriver() override;
		uint32_t getTicks() override;
		bool doQuit() override;

	private:
		SDLFlipdotDriver *_driver = nullptr;
		SDL_Window *_window = nullptr;
};

typedef PCPlatform Platform;
