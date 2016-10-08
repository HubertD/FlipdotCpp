#pragma once

#include "../Virtual/VirtualFlipdotDriver.h"
#include <SDL2/SDL.h>

class IPlatform;
class ScreenBuffer;

class SDLFlipdotDriver: public VirtualFlipdotDriver
{
	public:
		SDLFlipdotDriver(IPlatform &platform, SDL_Window* window, unsigned numPanelsX, unsigned numPanelsY);
		virtual ~SDLFlipdotDriver();

		void update(unsigned ticks) override;
		void redraw();

	protected:
		void onUpdateColumn(unsigned column) override;

	private:
		static const int DOT_WIDTH = 20;
		static const int DOT_HEIGHT = 20;
		static const int REDRAW_INTERVAL_MS = 100;

		IPlatform& _platform;
		SDL_Window* _window;
		SDL_Renderer* _renderer;
		unsigned _tLastUpdateColumn[COLUMNS] = { 0 };
		unsigned _tNextRedraw = 0;

		void drawOverlayRect(int x, int y, int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
		void drawDebugScreenBuffer(int x, int y, ScreenBuffer &buffer, ScreenBuffer &diffBuffer);
};
