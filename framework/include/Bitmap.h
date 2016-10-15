#pragma once

#include <stdint.h>
#include <IDrawable.h>

class Framebuffer;

class Bitmap : public IDrawable
{
	public:
		Bitmap(const uint8_t *data, int width, int height);
		bool getPixel(int x, int y) const override;
		void draw(Framebuffer& fb, int x, int y, bool doInvert=false) const override;

	private:
		const uint8_t *_data;
		const int _width;
		const int _height;

};
