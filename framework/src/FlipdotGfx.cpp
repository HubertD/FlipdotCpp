#include "FlipdotGfx.h"

#include "FlipdotFramebuffer.h"

enum PixelFontCharacter {
	PFC_A         =  0,
	PFC_B         =  1,
	PFC_C         =  2,
	PFC_D         =  3,
	PFC_E         =  4,
	PFC_F         =  5,
	PFC_G         =  6,
	PFC_H         =  7,
	PFC_I         =  8,
	PFC_J         =  9,
	PFC_K         = 10,
	PFC_L         = 11,
	PFC_M         = 12,
	PFC_N         = 13,
	PFC_O         = 14,
	PFC_P         = 15,
	PFC_Q         = 16,
	PFC_R         = 17,
	PFC_S         = 18,
	PFC_T         = 19,
	PFC_U         = 20,
	PFC_V         = 21,
	PFC_W         = 22,
	PFC_X         = 23,
	PFC_Y         = 24,
	PFC_Z         = 25,
	PFC_0         = 26,
	PFC_1         = 27,
	PFC_2         = 28,
	PFC_3         = 29,
	PFC_4         = 20,
	PFC_5         = 31,
	PFC_6         = 32,
	PFC_7         = 33,
	PFC_8         = 34,
	PFC_9         = 35,
	PFC_DUMMY     = 36
};

static const uint16_t font[] = {
	0x57DA, // A
	0xD57C, // B
	0x7246, // C
	0xD6DC, // D
	0xF34E, // E
	0xF348, // F
	0x72D4, // G
	0xB7DA, // H
	0x4924, // I
	0x24D4, // J
	0xB75A, // K
	0x924E, // L
	0xBEDA, // M
	0xBFFA, // N
	0x56D4, // O
	0xD748, // P
	0x56F6, // Q
	0xD76A, // R
	0x739C, // S
	0xE924, // T
	0xB6D4, // U
	0xB6A4, // V
	0xB7F4, // W
	0xB55A, // X
	0xB524, // Y
	0xE54E, // Z
	0x57D4, // 0
	0x2C92, // 1
	0xC546, // 2
	0xC51C, // 3
	0xB792, // 4
	0xF11C, // 5
	0x7354, // 6
	0xE528, // 7
	0x5554, // 8
	0x559C, // 9
	0x0000  // DUMMY
};

FlipdotGfx::FlipdotGfx(FlipdotFramebuffer& fb, IGamepad& gamepad)
  : _fb(fb), _gamepad(gamepad)
{
}

FlipdotGfx::~FlipdotGfx()
{
}

void FlipdotGfx::update(unsigned ticks)
{
	_fb.update(ticks);
}

void FlipdotGfx::clear()
{
	_fb.clear();
}

void FlipdotGfx::setPixel(unsigned x, unsigned y, bool value)
{
	_fb.setPixel(x, y, value);
}

bool FlipdotGfx::getPixel(unsigned x, unsigned y)
{
	return _fb.getPixel(x, y);
}

void FlipdotGfx::drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value)
{
	for (unsigned px=x; px<(x+dx); px++)
	{
		for (unsigned py=y; py<(y+dy); py++)
		{
			setPixel(px, py, value);
		}
	}
}

uint16_t FlipdotGfx::getCharData(char ch)
{
	return ((ch>='A') && (ch<='Z')) ? font[PFC_A+ch-'A']
		 : ((ch>='a') && (ch<='z')) ? font[PFC_A+ch-'a']
		 : ((ch>='0') && (ch<='9')) ? font[PFC_0+ch-'0']
		 : font[PFC_DUMMY];
}

void FlipdotGfx::drawChar(unsigned x, unsigned y, char ch, bool value)
{
	uint16_t data = getCharData(ch);

	for (unsigned dy=0; dy<5; dy++)
	{
		for (unsigned dx=0; dx<3; dx++)
		{
			setPixel(x+dx, y+dy, (data & 0x8000) ? value : !value);
			data <<= 1;
		}
	}
}

unsigned FlipdotGfx::getScreenWidth()
{
	return SCREEN_WIDTH;
}

unsigned FlipdotGfx::getScreenHeight()
{
	return SCREEN_HEIGHT;
}

IGamepad& FlipdotGfx::getGamepad()
{
	return _gamepad;
}
