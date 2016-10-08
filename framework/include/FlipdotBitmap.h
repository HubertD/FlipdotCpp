#pragma once

#include <stdint.h>
#include <FlipdotGfx.h>

class FlipdotBitmap
{
	public:
		FlipdotBitmap(const uint8_t *data, int width, int height);
		bool getPixel(int x, int y) const;
		void draw(FlipdotGfx &gfx, int x, int y, bool doInvert=false) const;

	private:
		const uint8_t *_data;
		const int _width;
		const int _height;

};
