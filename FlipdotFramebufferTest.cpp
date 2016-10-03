#include "driver/VCD/VcdFlipdotDriver.h"
#include "FlipdotFramebuffer.h"
#include "FlipdotGfx.h"
#include <stdint.h>

int main()
{
	VcdFlipdotDriver driver;
	FlipdotFramebuffer<2,2> framebuffer(driver);
	FlipdotGfx gfx(framebuffer);

	framebuffer.init();
	gfx.clear();
}
