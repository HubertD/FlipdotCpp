#include "SDLPlatform.h"

#include <FlipdotFramebuffer.h>

SDLPlatform::SDLPlatform()
{
}

void SDLPlatform::init()
{
	SDL_Init(SDL_INIT_VIDEO);
	_window = SDL_CreateWindow("Flipdot", 100, 100, 1000, 800, SDL_WINDOW_SHOWN);
	_driver = new SDLFlipdotDriver(*this, _window, 2, 2);
	_framebuffer = new FlipdotFramebuffer(*_driver);
}

void SDLPlatform::done()
{
	SDL_DestroyWindow( _window );
	SDL_Quit();
}

FlipdotFramebuffer& SDLPlatform::getFramebuffer()
{
	return *_framebuffer;
}

uint32_t SDLPlatform::getTicks()
{
	return SDL_GetTicks();
}

bool SDLPlatform::doQuit()
{
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		if( e.type == SDL_QUIT ) {
			return true;
		}
	}

	return false;
}
