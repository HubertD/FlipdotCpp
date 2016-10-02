#pragma once

#include "IFlipdotFramebuffer.h"
#include <SDL2/SDL.h>

/* TODO make timing more realistic (update column-wise, need time...) */

class SDLFlipdotFramebuffer : public IFlipdotFramebuffer
{
	public:
		SDLFlipdotFramebuffer(SDL_Window* window);
		~SDLFlipdotFramebuffer() override {};

		void init() override;
		void flush() override;
		void update() override;

		virtual void clear() override;
		virtual void setPixel(unsigned x, unsigned y, bool value) override;

	private:
		static const unsigned NUM_PIXELS_X = 32;
		static const unsigned NUM_PIXELS_Y = 40;

		SDL_Window* _window;
		SDL_Renderer *_renderer;

		bool _buffer[NUM_PIXELS_Y][NUM_PIXELS_X];
		void redraw();
};
