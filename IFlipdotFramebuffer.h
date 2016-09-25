#pragma once

class IFlipdotFramebuffer
{

	public:
		IFlipdotFramebuffer();

		virtual void init() = 0;
		virtual void flush() = 0;
		virtual void update() = 0;

		virtual void clear() = 0;
		virtual void setPixel(unsigned x, unsigned y, bool value) = 0;

};
