#include <FlipdotFramebuffer.h>
#include <FlipdotGfx.h>
#include <games/GameFactory.h>
#include <Platform.h>

int main(void)
{
	Platform platform;
	platform.init();

	IFlipdotDriver& driver = platform.getFlipdotDriver();
	FlipdotFramebuffer framebuffer(driver);
	framebuffer.configurePanel(0,  0, 20, FlipdotPanel::Orientation::DEG_180);
	framebuffer.configurePanel(1,  0,  0, FlipdotPanel::Orientation::DEG_180);
	framebuffer.configurePanel(2, 16,  0, FlipdotPanel::Orientation::DEG_0);
	framebuffer.configurePanel(3, 16, 20, FlipdotPanel::Orientation::DEG_0);

	FlipdotGfx gfx(framebuffer);
	framebuffer.init();

	IGame *game = GameFactory::createGame(GameFactory::Game::SCREENSAVER, gfx);
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
