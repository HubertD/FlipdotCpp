#include <FlipdotTypes.h>
#include <FlipdotFramebuffer.h>
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
	framebuffer.init();

	Environment env(framebuffer, gamepad);

	IGame *game = GameFactory::createGame(GameFactory::Game::TETRIS, env);
	game->init(0);

	while (!platform.doQuit())
	{
		platform.update();
		unsigned now = platform.getTicks();
		env.setCurrentTime(now);
		game->update(now);
		framebuffer.update(now);
	}

	platform.done();
	return 0;
}
