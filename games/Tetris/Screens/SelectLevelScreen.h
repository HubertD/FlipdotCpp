#include "../TetrisScreen.h"

class SelectLevelScreen : public TetrisScreen
{
	public:
		using TetrisScreen::TetrisScreen;

	protected:

		void onEnter()
		{

			draw();
		}

		void draw()
		{
			_gfx.clear();
			_gfx.drawText(2, 1, (char*)"SELECT", FlipdotColor::BLACK, Orientation::DEG_0, 1);
			_gfx.drawText(2, 8, (char*)"LEVEL", FlipdotColor::BLACK, Orientation::DEG_0, 2);

			_gfx.drawChar(15, 17, '_');
			_gfx.drawChar(15, 15, '0');
			/*
			  display_draw_character(15, 15, PFC_0+startLevel, 1, CHARACTER_ROTATION_NONE);
			*/
		}

		void onUpdate()
		{

			if (timeSinceEntered() > 10000) {
				setNextState(TetrisState::LOGO);
				return;
			}

		}

};
