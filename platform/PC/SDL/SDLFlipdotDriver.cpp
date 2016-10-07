#include "SDLFlipdotDriver.h"

SDLFlipdotDriver::SDLFlipdotDriver(SDL_Window* window, unsigned numPanelsX, unsigned numPanelsY)
  : VirtualFlipdotDriver(numPanelsX, numPanelsY),
	_window(window)
{
	_renderer = SDL_CreateRenderer(_window, -1, 0);
}

SDLFlipdotDriver::~SDLFlipdotDriver()
{
}

void SDLFlipdotDriver::onUpdateColumn(unsigned column)
{
	_tLastUpdateColumn[column] = SDL_GetTicks();
	redraw();
}

void SDLFlipdotDriver::update(unsigned ticks)
{
	VirtualFlipdotDriver::update(ticks);
	if (ticks <= _tNextRedraw)
	{
		redraw();
	}
}

void SDLFlipdotDriver::redraw()
{
	SDL_SetRenderDrawColor( _renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_SetRenderDrawBlendMode(_renderer, SDL_BLENDMODE_BLEND);
	SDL_RenderClear(_renderer);

	for (int y=0; y<(int)getHeight(); y++)
	{
		for (int x=0; x<(int)getWidth(); x++)
		{
			SDL_Rect rect = {x*(int)DOT_WIDTH, y*(int)DOT_HEIGHT, DOT_WIDTH, DOT_HEIGHT};

			if (getDotColor(x,y)) {
				SDL_SetRenderDrawColor(_renderer, 0x00, 0x00, 0x00, 0xFF);
			} else {
				SDL_SetRenderDrawColor(_renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}

			SDL_RenderFillRect(_renderer, &rect );
		}
	}

	unsigned now = SDL_GetTicks();

	drawOverlayRect(0, 0, 16, 20, 0xFF, 0, 0, 0x20);
	drawOverlayRect(16, 0, 16, 20, 0, 0xFF, 0, 0x20);
	drawOverlayRect(0, 20, 16, 20, 0, 0, 0xFF, 0x20);
	drawOverlayRect(16, 20, 16, 20, 0xFF, 0xFF, 0, 0x20);

	for (unsigned i=0; i<COLUMNS; i++)
	{
		if (_tLastUpdateColumn[i]==0)
		{
			continue;
		}

		unsigned deltaT = now - _tLastUpdateColumn[i];
		if (deltaT < 500)
		{
			drawOverlayRect(i, 0, 1, 40, 0xFF, 0, 0, 100-(deltaT/5));
			drawOverlayRect(31-i, 0, 1, 40, 0xFF, 0, 0, 100-(deltaT/5));
		}
	}

	SDL_RenderPresent(_renderer);
	_tNextRedraw = now + 100;
}

void SDLFlipdotDriver::drawOverlayRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	SDL_SetRenderDrawColor(_renderer, r, g, b, a);
	SDL_Rect rect = {x*DOT_WIDTH, y*DOT_HEIGHT, w*DOT_WIDTH, h*DOT_HEIGHT};
	SDL_RenderFillRect(_renderer, &rect );
}