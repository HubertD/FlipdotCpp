#include <FlipdotTypes.h>
#include <games/GameFactory.h>
#include <Platform.h>
#include <Environment.h>
#include <Framebuffer.h>

int main(void)
{
	Platform platform;
	platform.init();

	IGamepad& gamepad = platform.getGamepad();
	gamepad.init();

	Framebuffer& framebuffer = platform.getFramebuffer();
	framebuffer.init();

	Environment env(framebuffer, gamepad);

	IGame *game = GameFactory::createGame(GameFactory::Game::TETRIS, env);
	game->init();

	while (!platform.doQuit())
	{
		platform.update();
		env.setCurrentTime(platform.getTicks());
		game->update();
		framebuffer.update(env.now);
	}

	platform.done();
	return 0;
}
