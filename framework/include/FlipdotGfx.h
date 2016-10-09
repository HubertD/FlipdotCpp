#pragma once

#include <stdint.h>
#include <FlipdotTypes.h>

class FlipdotFramebuffer;
class FlipdotBitmap;
class IGamepad;

class FlipdotGfx
{
	public:
		FlipdotGfx(FlipdotFramebuffer &framebuffer, IGamepad& gamepad);
		FlipdotGfx( const FlipdotGfx& other ) = delete;
		FlipdotGfx& operator=( const FlipdotGfx& ) = delete;
		~FlipdotGfx();

		void update(unsigned ticks);

		void clear();
		void setPixel(unsigned x, unsigned y, bool value);
		bool getPixel(unsigned x, unsigned y);
		void drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value);
		void drawChar(unsigned x, unsigned y, char ch, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0);
		void drawText(unsigned x, unsigned y, char *text, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void drawNumber(unsigned x, unsigned y, unsigned number, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void drawBitmap(int x, int y, const FlipdotBitmap &bitmap, bool doInvert=false);

		unsigned getScreenWidth();
		unsigned getScreenHeight();

		IGamepad& getGamepad();

	private:
		FlipdotFramebuffer &_fb;
		IGamepad& _gamepad;
		uint16_t getCharData(char ch);

		int getCharStepX(Orientation orientation, int spacing);
		int getCharStepY(Orientation orientation, int spacing);

};
