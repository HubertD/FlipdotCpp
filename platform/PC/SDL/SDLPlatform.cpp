#include "SDLPlatform.h"
#include <iostream>
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

void SDLPlatform::update()
{
	SDL_Event e;
	while( SDL_PollEvent( &e ) != 0 )
	{
		handleSDLEvent(e);
	}
}

void SDLPlatform::handleSDLEvent(SDL_Event& event)
{
	switch (event.type)
	{
		case SDL_KEYDOWN:
		case SDL_KEYUP:
			handleKeyEvent(event.key);
			break;

		case SDL_QUIT:
			_doQuit = true;
			break;

	}
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
	return _doQuit;
}

IGamepad& SDLPlatform::getGamepad()
{
	return _gamepad;
}

void SDLPlatform::handleKeyEvent(SDL_KeyboardEvent &key)
{
	GamepadKey gamepadKey = GamepadKey::KEY_NONE;

	switch (key.keysym.sym)
	{
		case SDLK_LEFT:
			gamepadKey = GamepadKey::KEY_LEFT;
			break;
		case SDLK_RIGHT:
			gamepadKey = GamepadKey::KEY_RIGHT;
			break;
		case SDLK_UP:
			gamepadKey = GamepadKey::KEY_UP;
			break;
		case SDLK_DOWN:
			gamepadKey = GamepadKey::KEY_DOWN;
			break;
		case SDLK_SPACE:
			gamepadKey = GamepadKey::KEY_SELECT;
			break;
		case SDLK_RETURN:
			gamepadKey = GamepadKey::KEY_START;
			break;
		case SDLK_a:
			gamepadKey = GamepadKey::KEY_A;
			break;
		case SDLK_s:
		case SDLK_b:
			gamepadKey = GamepadKey::KEY_B;
			break;
		default:
			return;
	}

	if (key.type == SDL_KEYDOWN) {
		_gamepad.injectKeyPress(gamepadKey);
	} else if (key.type == SDL_KEYUP) {
		_gamepad.injectKeyRelease(gamepadKey);
	}

}
