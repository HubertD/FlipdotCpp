#include <FlipdotTypes.h>
#include <FlipdotFramebuffer.h>
#include <FlipdotGfx.h>
#include <games/GameFactory.h>
#include <Platform.h>
#include <Environment.h>

int main(void)
{
	Platform platform;
	platform.init();

	IGamepad& gamepad = platform.getGamepad();
	gamepad.init();

	FlipdotFramebuffer& framebuffer = platform.getFramebuffer();
	FlipdotGfx gfx(framebuffer);
	framebuffer.init();

	Environment env(gfx, gamepad);

	IGame *game = GameFactory::createGame(GameFactory::Game::TETRIS, env);
	game->init(0);

	while (!platform.doQuit())
	{
		platform.update();
		unsigned now = platform.getTicks();
		env.setCurrentTime(now);
		game->update(now);
		gfx.update(now);
	}

	platform.done();
	return 0;
}
