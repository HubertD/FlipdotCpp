#include <Framebuffer.h>
#include <platform/PC/VCD/VCDPlatform.h>

int main(void)
{
	VCDPlatform platform;
	platform.init();
	platform.setQuitUTicks(500*1000);

	auto& framebuffer = platform.getFramebuffer();
	framebuffer.init();

	framebuffer.clear();
	for (int i=0; i<32; i++)
	{
		framebuffer.setPixel(i, i, true);
	}

	while (!platform.doQuit())
	{
		platform.update();
		framebuffer.update(platform.getTicks());
	}

	platform.done();
	return 0;
}
