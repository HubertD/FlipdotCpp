#pragma once

class IFlipdotFramebuffer
{

	public:
		IFlipdotFramebuffer() {};
		virtual ~IFlipdotFramebuffer() {};

		virtual void init() = 0;
		virtual void flush() = 0;
		virtual void update() = 0;

		virtual void clear() = 0;
		virtual void setPixel(unsigned x, unsigned y, bool value) = 0;
		virtual bool getPixel(unsigned x, unsigned y) = 0;

		virtual unsigned getScreenWidth() = 0;
		virtual unsigned getScreenHeight() = 0;

};
