#include <ScreenBuffer.h>

void ScreenBuffer::copyColumnFromOther(ScreenBuffer& other, unsigned x, bool copySetBits, bool copyClearedBits)
{
	for (unsigned y=0; y<SCREEN_HEIGHT; y+=8)
	{
		uint8_t data  = get8Pixels(x, y);
		if (copySetBits) {
			data |= other.get8Pixels(x, y);
		}
		if (copyClearedBits) {
			data &= other.get8Pixels(x, y);
		}
		set8Pixels(x, y, data);
	}
}

bool ScreenBuffer::otherHasSetBitsWeHaveNot(ScreenBuffer& other, unsigned x)
{
	for (unsigned y=0; y<SCREEN_HEIGHT; y+=8)
	{
		uint8_t here = get8Pixels(x, y);
		uint8_t there = other.get8Pixels(x, y);

		if ( (here | there) != here) {
			return true;
		}
	}
	return false;
}
