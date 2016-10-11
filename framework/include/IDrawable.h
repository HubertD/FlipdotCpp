#pragma once

class FlipdotGfx;

class IDrawable
{
	public:
		virtual ~IDrawable() {};
		virtual bool getPixel(int x, int y) const = 0;
		virtual void draw(FlipdotGfx &gfx, int x, int y, bool doInvert=false) const = 0;
};

