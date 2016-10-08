#include <ScreenBuffer.h>

void ScreenBuffer::copyFrom(
	ScreenBuffer& source, unsigned sourceX, unsigned sourceY,
	unsigned destX, unsigned destY, unsigned width, unsigned height,
	bool copySetPixels, bool copyClearedPixels)
{

	for (unsigned i=0; i<width; i++)
	{
		copyColumnFrom(source, sourceX+i, sourceY, destX+i, destY, height, copySetPixels, copyClearedPixels);
	}

}

inline void ScreenBuffer::copyColumnFrom(
	ScreenBuffer& source, unsigned sourceX, unsigned sourceY,
	unsigned destX, unsigned destY, unsigned height,
	bool copySetPixels, bool copyClearedPixels)
{
	for (unsigned i=0; i<height; i++) {
		copyPixelFrom(source, sourceX, sourceY+i, destX, destY+i, copySetPixels, copyClearedPixels);
	}
}

inline void ScreenBuffer::copyPixelFrom(
	ScreenBuffer &source,
	unsigned sourceX, unsigned sourceY,
	unsigned destX, unsigned destY,
	bool copySetPixels, bool copyClearedPixels)
{

	bool data = source.getPixel(sourceX, sourceY);

	if ((data && copySetPixels) || ((!data) && copyClearedPixels))
	{
		setPixel(destX, destY, data);
	}
}
