#include <FlipdotTypes.h>
#include <FlipdotFramebuffer.h>
#include <FlipdotGfx.h>
#include <games/GameFactory.h>
#include <Platform.h>

int main(void)
{
	Platform platform;
	platform.init();

	FlipdotFramebuffer& framebuffer = platform.getFramebuffer();

	FlipdotGfx gfx(framebuffer);
	framebuffer.init();

	IGame *game = GameFactory::createGame(GameFactory::Game::TESTSCREEN, gfx);
	game->init(0);

	while (!platform.doQuit())
	{
		platform.update();
		unsigned now = platform.getTicks();
		game->update(now);
		gfx.update(now);
	}

	platform.done();
	return 0;
}
