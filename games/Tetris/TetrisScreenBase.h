#pragma once

#include <FlipdotGfx.h>
#include <IGamepad.h>

class TetrisGame;
class TetrisScreens;
class TetrisVariables;
class FlipdotGfx;
class IGamepad;

class TetrisScreenBase
{

	protected:
		unsigned now();
		FlipdotGfx &getGfx();
		IGamepad &getGamepad();
		TetrisScreens &getScreens();
		TetrisVariables &getVariables();
		unsigned timeSinceEntered();
		void setNextScreen(TetrisScreenBase& screen);

		bool isAnyKeyPressed();
		bool wasKeyPressed(GamepadKey key);
		bool wasKeyReleased(GamepadKey key);
		bool wasContinuePressed();
		bool wasNextPressed();
		bool wasPreviousPressed();

		void clearScreen();
		void setPixel(unsigned x, unsigned y, bool value);
		void drawRect(unsigned x, unsigned y, unsigned dx, unsigned dy, bool value);
		void drawChar(unsigned x, unsigned y, char ch, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0);
		void drawText(unsigned x, unsigned y, char *text, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void drawNumber(unsigned x, unsigned y, unsigned number, FlipdotColor color=FlipdotColor::BLACK, Orientation orientation = Orientation::DEG_0, int spacing=0);
		void drawObject(int x, int y, const IDrawable &drawable, bool doInvert=false);


	public:
		TetrisScreenBase(TetrisGame &game);
		TetrisScreenBase( const TetrisScreenBase& other ) = delete;
		TetrisScreenBase& operator=( const TetrisScreenBase& ) = delete;
		virtual ~TetrisScreenBase();

		virtual void enter() {};
		virtual void update() {};
		virtual void leave() {};

	private:
		TetrisGame& _game;

};
