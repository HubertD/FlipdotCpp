#pragma once

#include <stdint.h>

class FlipdotFramebuffer;

class FlipdotGfx
{
	public:
		FlipdotGfx(FlipdotFramebuffer &framebuffer);
		~FlipdotGfx();

		void update(unsigned ticks);

		void clear();
		void setPixel(unsigned x, unsigned y, bool value);
		bool getPixel(unsigned x, unsigned y);
		void drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value);
		void drawChar(unsigned x, unsigned y, char ch, bool invert);

		unsigned getScreenWidth();
		unsigned getScreenHeight();

	private:
		FlipdotFramebuffer &_fb;
		uint16_t getCharData(char ch);

};
