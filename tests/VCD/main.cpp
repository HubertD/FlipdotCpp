#include <FlipdotFramebuffer.h>
#include <FlipdotGfx.h>
#include <platform/PC/VCD/VCDPlatform.h>

int main(void)
{
	VCDPlatform platform;
	platform.init();
	platform.setQuitUTicks(500*1000);

	IFlipdotDriver& driver = platform.getFlipdotDriver();
	FlipdotFramebuffer framebuffer(driver);
	FlipdotGfx gfx(framebuffer);
	framebuffer.init();

	gfx.clear();
	for (int i=0; i<32; i++)
	{
		gfx.setPixel(i, i, true);
	}

	while (!platform.doQuit())
	{
		platform.update();
		gfx.update(platform.getTicks());
	}

	platform.done();
	return 0;
}
