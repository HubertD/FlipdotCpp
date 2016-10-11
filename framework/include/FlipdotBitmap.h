#pragma once

#include <stdint.h>
#include <FlipdotGfx.h>
#include <IDrawable.h>

class FlipdotBitmap : public IDrawable
{
	public:
		FlipdotBitmap(const uint8_t *data, int width, int height);
		bool getPixel(int x, int y) const override;
		void draw(FlipdotGfx &gfx, int x, int y, bool doInvert=false) const override;

	private:
		const uint8_t *_data;
		const int _width;
		const int _height;

};
