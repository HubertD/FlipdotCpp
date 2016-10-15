#include <FlipdotBitmap.h>
#include <Framebuffer.h>

FlipdotBitmap::FlipdotBitmap(const uint8_t *data, int width, int height)
  : _data(data), _width(width), _height(height)
{
}

bool FlipdotBitmap::getPixel(int x, int y) const
{
	int bitPosition = y*_width + x;
	int bytePosition = bitPosition / 8;
	uint8_t bitMask = (0x80 >> (bitPosition % 8));

	return (_data[bytePosition] & bitMask) != 0;
}

void FlipdotBitmap::draw(Framebuffer& fb, int x, int y, bool doInvert /*=false*/) const
{
	for (int iy=0; iy<_height; iy++) {
		for (int ix=0; ix<_width; ix++)
		{
			bool value = getPixel(ix, iy);
			if (doInvert) { value = !value; }
			fb.setPixel(x+ix, y+iy, value);
		}
	}
}
