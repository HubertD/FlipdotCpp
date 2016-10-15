#pragma once

class FlipdotFramebuffer;

class IDrawable
{
	public:
		virtual ~IDrawable() {};
		virtual bool getPixel(int x, int y) const = 0;
		virtual void draw(FlipdotFramebuffer &fb, int x, int y, bool doInvert=false) const = 0;
};

