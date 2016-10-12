#pragma once

#include <FlipdotConfig.h>
#include <stdint.h>

class ScreenBuffer
{
	public:
		bool getPixel(int x, int y);
		void setPixel(int x, int y, bool value);

		uint8_t get8Pixels(int x, int y);
		void set8Pixels(int x, int y, uint8_t value);
		void or8Pixels(int x, int y, uint8_t value);
		void and8Pixels(int x, int y, uint8_t value);

		void copyFrom(
			ScreenBuffer &source,
			int sourceX, int sourceY,
			int destX, int destY,
			int width, int height,
			bool copySetPixels=true, bool copyClearedPixels=true
		);

		uint32_t getColumnPixels(int x, int startY, int numPixels, int step=+1);


	private:
		static constexpr unsigned BYTES_PER_COLUMN = ((SCREEN_HEIGHT - 1) / 8) + 1;
		uint8_t _data[SCREEN_WIDTH * BYTES_PER_COLUMN] = { 0 };

		static constexpr unsigned getBytePosition(int x, int y);

		void copyColumnFrom(
			ScreenBuffer &source,
			int sourceX, int sourceY,
			int destX, int destY,
			int height,
			bool copySetPixels=true, bool copyClearedPixels=true
		);

		void copyPixelFrom(
			ScreenBuffer &source,
			int sourceX, int sourceY,
			int destX, int destY,
			bool copySetPixels=true, bool copyClearedPixels=true
		);
};

inline constexpr unsigned ScreenBuffer::getBytePosition(int x, int y)
{
	return x*BYTES_PER_COLUMN + (y/8);
}

inline bool ScreenBuffer::getPixel(int x, int y)
{
	if ( (x<0) || (x>=SCREEN_WIDTH) ) { return false; }
	if ( (y<0) || (y>=SCREEN_HEIGHT) ) { return false; }

	unsigned bitmask = 1 << (y % 8);
	unsigned bytePos = getBytePosition(x, y);
	return (_data[bytePos] & bitmask) != 0;
}

inline uint8_t ScreenBuffer::get8Pixels(int x, int y)
{
	return _data[getBytePosition(x, y)];
}

inline void ScreenBuffer::setPixel(int x, int y, bool value)
{
	if ( (x<0) || (x>=SCREEN_WIDTH) ) { return; }
	if ( (y<0) || (y>=SCREEN_HEIGHT) ) { return; }

	unsigned bitmask = 1 << (y % 8);
	unsigned bytePos = getBytePosition(x, y);

	if (value) {
		_data[bytePos] |= bitmask;
	} else {
		_data[bytePos] &= ~bitmask;
	}
}

inline void ScreenBuffer::set8Pixels(int x, int y, uint8_t value)
{
	_data[getBytePosition(x, y)] = value;
}

inline void ScreenBuffer::or8Pixels(int x, int y, uint8_t value)
{
	_data[getBytePosition(x, y)] |= value;
}

inline void ScreenBuffer::and8Pixels(int x, int y, uint8_t value)
{
	_data[getBytePosition(x, y)] &= value;
}
