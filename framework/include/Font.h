#pragma once

#include <FlipdotTypes.h>

class FlipdotFramebuffer;

class Font
{
	public:
		static void drawText(FlipdotFramebuffer& fb, int x, int y, char *text, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		static void drawNumber(FlipdotFramebuffer& fb, int x, int y, unsigned number, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		static void drawChar(FlipdotFramebuffer& fb, int x, int y, char ch, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0);

	private:
		static uint16_t getCharData(char ch);

		static int getCharStepX(Orientation orientation, int spacing);
		static int getCharStepY(Orientation orientation, int spacing);

};

