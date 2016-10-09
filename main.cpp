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
	IGamepad& gamepad = platform.getGamepad();
	FlipdotGfx gfx(framebuffer, gamepad);
	framebuffer.init();
	gamepad.init();

	IGame *game = GameFactory::createGame(GameFactory::Game::TETRIS, gfx);
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
