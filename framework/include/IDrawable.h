#pragma once

class Framebuffer;

class IDrawable
{
	public:
		virtual ~IDrawable() {};
		virtual void draw(Framebuffer &fb, int x, int y, bool doInvert=false) const = 0;
};

