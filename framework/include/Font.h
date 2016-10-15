#pragma once

#include <FlipdotTypes.h>

class Framebuffer;

class Font
{
	public:
		static void drawText(Framebuffer& fb, int x, int y, char *text, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		static void drawNumber(Framebuffer& fb, int x, int y, unsigned number, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		static void drawChar(Framebuffer& fb, int x, int y, char ch, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0);

	private:
		static uint16_t getCharData(char ch);

		static int getCharStepX(Orientation orientation, int spacing);
		static int getCharStepY(Orientation orientation, int spacing);

};

