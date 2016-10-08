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

		void copyColumnFromOther(ScreenBuffer &other, unsigned x, bool copySetBits, bool copyClearedBits);
		bool otherHasSetBitsWeHaveNot(ScreenBuffer &other, unsigned x);

	private:
		static constexpr unsigned BYTES_PER_COLUMN = ((SCREEN_HEIGHT - 1) / 8) + 1;
		uint8_t _data[SCREEN_WIDTH * BYTES_PER_COLUMN] = { 0 };

		static constexpr unsigned getBytePosition(unsigned x, unsigned y);

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

