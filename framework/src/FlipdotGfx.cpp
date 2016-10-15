#include "FlipdotGfx.h"

#include "FlipdotFramebuffer.h"
#include "FlipdotBitmap.h"

FlipdotGfx::FlipdotGfx(FlipdotFramebuffer& fb)
  : _fb(fb)
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

void FlipdotGfx::setPixel(int x, int y, bool value)
{
	_fb.setPixel(x, y, value);
}

bool FlipdotGfx::getPixel(int x, int y)
{
	return _fb.getPixel(x, y);
}

void FlipdotGfx::drawRect(int x, int y, int dx, int dy, bool value)
{
	for (int px=x; px<(x+dx); px++)
	{
		for (int py=y; py<(y+dy); py++)
		{
			setPixel(px, py, value);
		}
	}
}

void FlipdotGfx::draw(int x, int y, const IDrawable &drawable, bool doInvert)
{
	drawable.draw(*this, x, y, doInvert);
}
