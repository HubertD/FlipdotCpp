#include "../gfx/SDLFlipdotFramebuffer.h"

SDLFlipdotFramebuffer::SDLFlipdotFramebuffer(SDL_Window* window)
  : _window(window), _renderer(nullptr)
{
	clear();
}

void SDLFlipdotFramebuffer::init()
{
	_renderer = SDL_CreateRenderer(_window, -1, 0);
	clear();
	flush();
}

void SDLFlipdotFramebuffer::flush()
{
	redraw();
}

void SDLFlipdotFramebuffer::update()
{
	redraw();
}

void SDLFlipdotFramebuffer::clear()
{
	for (unsigned y=0; y<NUM_PIXELS_Y; y++)
	{
		for (unsigned x=0; x<NUM_PIXELS_X; x++)
		{
			_buffer[y][x] = false;
		}
	}
}

void SDLFlipdotFramebuffer::setPixel(unsigned x, unsigned y, bool value)
{
	_buffer[y][x] = value;
}

void SDLFlipdotFramebuffer::redraw()
{
	if (_renderer == nullptr) {
		return;
	}

	SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear(_renderer);

	for (unsigned y=0; y<NUM_PIXELS_Y; y++)
	{
		for (unsigned x=0; x<NUM_PIXELS_X; x++)
		{
			SDL_Rect rect = {x*DOT_WIDTH, y*DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT};

			if (_buffer[y][x]) {
				SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
			} else {
				SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}

			SDL_RenderFillRect(_renderer, &rect );
		}
	}

	SDL_RenderPresent(_renderer);
}

