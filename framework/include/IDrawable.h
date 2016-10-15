#pragma once

class Framebuffer;

class IDrawable
{
	public:
		virtual ~IDrawable() {};
		virtual bool getPixel(int x, int y) const = 0;
		virtual void draw(Framebuffer &fb, int x, int y, bool doInvert=false) const = 0;
};

