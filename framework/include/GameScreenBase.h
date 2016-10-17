#pragma once

#include <Framebuffer.h>

class Gamepad;
class Environment;

class GameScreenBase
{

	public:
		GameScreenBase(Environment& env);
		GameScreenBase( const GameScreenBase& other ) = delete;
		GameScreenBase& operator=( const GameScreenBase& ) = delete;
		virtual ~GameScreenBase();

		virtual void enter() {};
		virtual void update() {};
		virtual void leave() {};

	protected:
		Environment& _env;

		unsigned now();
		Framebuffer &getFramebuffer();
		Gamepad &getGamepad();

		bool isAnyKeyPressed();
		bool wasAnyKeyPressed();
		bool wasContinuePressed();
		bool wasNextPressed();
		bool wasPreviousPressed();

		void clearScreen();
		void setPixel(unsigned x, unsigned y, bool value);
		void drawRect(Rect rect, bool value);
		void drawChar(unsigned x, unsigned y, char ch, Color color=Color::BLACK, Orientation orientation = Orientation::DEG_0);
		void drawText(unsigned x, unsigned y, char *text, Color color=Color::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void drawNumber(unsigned x, unsigned y, unsigned number, Color color=Color::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void drawObject(int x, int y, const IDrawable &drawable, bool doInvert=false);

};
