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
		void draw(int x, int y, const IDrawable &drawable, bool doInvert=false);

	private:
		FlipdotFramebuffer &_fb;

};
