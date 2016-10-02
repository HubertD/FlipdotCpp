#include "VcdFlipdotDriver.h"
#include "FlipdotFramebuffer.h"
#include "FlipdotGfx.h"
#include <stdint.h>

int main()
{
	uint8_t buffer[192];
	VcdFlipdotDriver driver;
	FlipdotFramebuffer framebuffer(driver, 2, 2, buffer, sizeof(buffer));
	FlipdotGfx gfx(framebuffer);

	framebuffer.init();
	gfx.clear();
}
