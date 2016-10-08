#pragma once

#include <FlipdotConfig.h>
#include <stdint.h>

class ScreenBuffer
{
	public:
		bool getPixel(unsigned x, unsigned y);
		void setPixel(unsigned x, unsigned y, bool value);

		uint8_t get8Pixels(unsigned x, unsigned y);
		void set8Pixels(unsigned x, unsigned y, uint8_t value);
		void or8Pixels(unsigned x, unsigned y, uint8_t value);
		void and8Pixels(unsigned x, unsigned y, uint8_t value);

		void copyFrom(
			ScreenBuffer &source,
			unsigned sourceX, unsigned sourceY,
			unsigned destX, unsigned destY,
			unsigned width, unsigned height,
			bool copySetPixels=true, bool copyClearedPixels=true
		);

	private:
		static constexpr unsigned BYTES_PER_COLUMN = ((SCREEN_HEIGHT - 1) / 8) + 1;
		uint8_t _data[SCREEN_WIDTH * BYTES_PER_COLUMN] = { 0 };

		static constexpr unsigned getBytePosition(unsigned x, unsigned y);

		void copyColumnFrom(
			ScreenBuffer &source,
			unsigned sourceX, unsigned sourceY,
			unsigned destX, unsigned destY,
			unsigned height,
			bool copySetPixels=true, bool copyClearedPixels=true
		);

		void copyPixelFrom(
			ScreenBuffer &source,
			unsigned sourceX, unsigned sourceY,
			unsigned destX, unsigned destY,
			bool copySetPixels=true, bool copyClearedPixels=true
		);
};

inline constexpr unsigned ScreenBuffer::getBytePosition(unsigned x, unsigned y)
{
	return x*BYTES_PER_COLUMN + (y/8);
}

inline bool ScreenBuffer::getPixel(unsigned x, unsigned y)
{
	unsigned bitmask = 1 << (y % 8);
	unsigned bytePos = getBytePosition(x, y);
	return (_data[bytePos] & bitmask) != 0;
}

inline uint8_t ScreenBuffer::get8Pixels(unsigned x, unsigned y)
{
	return _data[getBytePosition(x, y)];
}

inline void ScreenBuffer::setPixel(unsigned x, unsigned y, bool value)
{
	unsigned bitmask = 1 << (y % 8);
	unsigned bytePos = getBytePosition(x, y);
	if (value) {
		_data[bytePos] |= bitmask;
	} else {
		_data[bytePos] &= ~bitmask;
	}
}

inline void ScreenBuffer::set8Pixels(unsigned x, unsigned y, uint8_t value)
{
	_data[getBytePosition(x, y)] = value;
}

inline void ScreenBuffer::or8Pixels(unsigned x, unsigned y, uint8_t value)
{
	_data[getBytePosition(x, y)] |= value;
}

inline void ScreenBuffer::and8Pixels(unsigned x, unsigned y, uint8_t value)
{
	_data[getBytePosition(x, y)] &= value;
}
