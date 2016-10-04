#pragma once

#include <SDL2/SDL.h>

#include "../../drivers/Virtual/VirtualFlipdotDriver.h"

class SDLFlipdotDriver: public VirtualFlipdotDriver
{
	public:
		SDLFlipdotDriver(SDL_Window* window, unsigned numPanelsX, unsigned numPanelsY);
		virtual ~SDLFlipdotDriver();
		void delayFlipDots() override;
		void redraw();
		void update(unsigned ticks);

	protected:
		void onUpdateColumn(unsigned column) override;

	private:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 15;
		static const int DELAY_OE_MS = 15;

		SDL_Window* _window;
		SDL_Renderer *_renderer;
		unsigned _tLastUpdateColumn[COLUMNS] = { 0 };
		unsigned _tNextRedraw = 0;

		void drawOverlayRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
};
