#pragma once

#include <stdint.h>
#include "IFlipdotGfx.h"

class FlipdotGfx : public IFlipdotGfx
{
	public:
		FlipdotGfx(IFlipdotFramebuffer &fb);
		void clear() override;
		void setPixel(unsigned x, unsigned y, bool value) override;
		void drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value) override;
		void drawChar(unsigned x, unsigned y, char ch, bool invert) override;

	private:
		IFlipdotFramebuffer &_fb;
		uint16_t getCharData(char ch);

};
