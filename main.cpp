#include <FlipdotFramebuffer.h>
#include <FlipdotGfx.h>
#include <games/GameFactory.h>
#include <Platform.h>

int main(void)
{
	Platform platform;
	platform.init();

	IFlipdotDriver& driver = platform.getFlipdotDriver();
	FlipdotFramebuffer<2,2> framebuffer(driver);
	FlipdotGfx gfx(framebuffer);
	framebuffer.init();

	IGame *game = GameFactory::createGame(GameFactory::Game::SCREENSAVER, gfx);
	game->init(0);

	while (!platform.doQuit())
	{
		unsigned now = platform.getTicks();
		game->update(now);
		gfx.update(now);
	}

	platform.done();
}
