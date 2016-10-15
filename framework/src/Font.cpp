#include <Font.h>
#include <Framebuffer.h>

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
	PFC_SPACE     = 36,
	PFC_COLON     = 37,
	PFC_EXCLAMATION = 38,
	PFC_UNDERSCORE  = 39
};

static const uint16_t font[] = {
	0x57DA, // A
	0xD75C, // B
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
	0xD75A, // R
	0x739C, // S
	0xE924, // T
	0xB6D4, // U
	0xB6A4, // V
	0xB6FA, // W
	0xB55A, // X
	0xB524, // Y
	0xE54E, // Z
	0x56D4, // 0
	0x2C92, // 1
	0xC546, // 2
	0xC51C, // 3
	0xB792, // 4
	0xF11C, // 5
	0x7354, // 6
	0xE524, // 7
	0x5554, // 8
	0x559C, // 9
	0x0000, // SPACE
	0x0820, // :
	0x4904, // !
	0x000E  // _
};

uint16_t Font::getCharData(char ch)
{
	if ((ch>='A') && (ch<='Z')) { return font[PFC_A+ch-'A']; }
	if ((ch>='a') && (ch<='z')) { return font[PFC_A+ch-'a']; }
    if ((ch>='0') && (ch<='9')) { return font[PFC_0+ch-'0']; }

    switch (ch)
    {
    	case '!':
    		return font[PFC_EXCLAMATION];
    	case ':':
    		return font[PFC_COLON];
    	case '_':
    		return font[PFC_UNDERSCORE];
    	default:
    		return font[PFC_SPACE];
    }
}

void Font::drawChar(Framebuffer& fb, int x, int y, char ch, FlipdotColor color, Orientation orientation)
{
	uint16_t data = getCharData(ch);

	bool foregroundValue = (color==FlipdotColor::BLACK);

	for (unsigned dy=0; dy<5; dy++)
	{
		for (unsigned dx=0; dx<3; dx++)
		{
			bool value = (data & 0x8000) ? foregroundValue : !foregroundValue;

			switch (orientation)
			{
				case Orientation::DEG_90:
					fb.setPixel(x+5-dy, y+dx-2, value);
					break;

				case Orientation::DEG_270:
					fb.setPixel(x+dy, y+(3-dx)-2, value);
					break;

				case Orientation::DEG_0:
				default: // TODO DEG_180
					fb.setPixel(x+dx, y+dy, value);
					break;
			}

			data <<= 1;
		}
	}
}

void Font::drawText(Framebuffer& fb, int x, int y, char* text, FlipdotColor color, Orientation orientation, int spacing)
{
	while (*text != 0)
	{
	    drawChar(fb, x, y, *text, color, orientation);
	    text++;
		x += getCharStepX(orientation, spacing);
		y += getCharStepY(orientation, spacing);
	}
}

void Font::drawNumber(Framebuffer& fb, int x, int y, unsigned number, FlipdotColor color, Orientation orientation, int spacing)
{
	do {
		x -= getCharStepX(orientation, spacing);
		y += getCharStepY(orientation, spacing);

	    drawChar(fb, x, y, '0'+(number % 10), color, orientation);

	    number /= 10;
	} while (number!=0);
}

int Font::getCharStepX(Orientation orientation, int spacing)
{
	return (orientation==Orientation::DEG_0) ? 4+spacing : 0;
}

int Font::getCharStepY(Orientation orientation, int spacing)
{
	switch (orientation)
	{
		case Orientation::DEG_270:
			return +(4 + spacing);

		case Orientation::DEG_90:
			return -(4 + spacing);

		default:
			return 0;
	}
}

