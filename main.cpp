#include <SDL2/SDL.h>

#include <FlipdotFramebuffer.h>
#include <FlipdotGfx.h>

#include "framework/drivers/SDL/SDLFlipdotDriver.h"
#include "games/GameFactory.h"

int main() {

	SDL_Init(SDL_INIT_VIDEO);
	auto window = SDL_CreateWindow("Flipdot", 100, 100, 640, 800, SDL_WINDOW_SHOWN);

	SDLFlipdotDriver driver(window, 2, 2);
	FlipdotFramebuffer<2,2> framebuffer(driver);
	FlipdotGfx gfx(framebuffer);
	framebuffer.init();

	IGame *game = GameFactory::createGame(GameFactory::Game::GAME_OF_LIFE, gfx);
	game->init(SDL_GetTicks());

	SDL_Event e;
	bool doQuit = false;
	while (!doQuit)
	{
		while( SDL_PollEvent( &e ) != 0 )
		{
			if( e.type == SDL_QUIT ) {
				doQuit = true;
				break;
			}
		}

		unsigned now = SDL_GetTicks();
		game->update(now);
		framebuffer.update();
		driver.update(now);
	}

	SDL_DestroyWindow( window );
	SDL_Quit();
	return 0;
}
