#include <ScreenBuffer.h>

void ScreenBuffer::copyFrom(
	ScreenBuffer& source, int sourceX, int sourceY,
	int destX, int destY, int width, int height,
	bool copySetPixels, bool copyClearedPixels)
{

	for (int i=0; i<width; i++)
	{
		copyColumnFrom(source, sourceX+i, sourceY, destX+i, destY, height, copySetPixels, copyClearedPixels);
	}

}

inline void ScreenBuffer::copyColumnFrom(
	ScreenBuffer& source, int sourceX, int sourceY,
	int destX, int destY, int height,
	bool copySetPixels, bool copyClearedPixels)
{
	for (int i=0; i<height; i++) {
		copyPixelFrom(source, sourceX, sourceY+i, destX, destY+i, copySetPixels, copyClearedPixels);
	}
}

inline void ScreenBuffer::copyPixelFrom(
	ScreenBuffer &source,
	int sourceX, int sourceY,
	int destX, int destY,
	bool copySetPixels, bool copyClearedPixels)
{

	bool data = source.getPixel(sourceX, sourceY);

	if ((data && copySetPixels) || ((!data) && copyClearedPixels))
	{
		setPixel(destX, destY, data);
	}
}

uint32_t ScreenBuffer::getColumnPixels(int x, int startY, int numPixels, int step)
{
	uint32_t result = 0;
	int y = startY;
	for (int i=0; i<numPixels; i++)
	{
		result <<= 1;
		if (getPixel(x, y)) {
			result |= 1;
		}
		y += step;
	}
	return result;
}

