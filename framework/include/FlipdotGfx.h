#pragma once

#include <stdint.h>
#include <FlipdotTypes.h>

class FlipdotFramebuffer;
class IDrawable;

class FlipdotGfx
{
	public:
		FlipdotGfx(FlipdotFramebuffer &framebuffer);
		FlipdotGfx( const FlipdotGfx& other ) = delete;
		FlipdotGfx& operator=( const FlipdotGfx& ) = delete;
		~FlipdotGfx();

		void update(unsigned ticks);

		void clear();
		void setPixel(int x, int y, bool value);
		bool getPixel(int x, int y);
		void drawRect(int x, int y, int dx, int dy, bool value);
		void drawChar(int x, int y, char ch, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0);
		void drawText(int x, int y, char *text, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void drawNumber(int x, int y, unsigned number, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void draw(int x, int y, const IDrawable &drawable, bool doInvert=false);

	private:
		FlipdotFramebuffer &_fb;
		uint16_t getCharData(char ch);

		int getCharStepX(Orientation orientation, int spacing);
		int getCharStepY(Orientation orientation, int spacing);

};
