#include "../TetrisScreen.h"

class IdleScreen : public TetrisScreen
{
	public:
		using TetrisScreen::TetrisScreen;

	protected:

		void onEnter()
		{
			_gfx.clear();
			_gfx.drawText(2, 1, (char*)"TETRIS", FlipdotColor::BLACK, Orientation::DEG_0, 1);
			_gfx.drawBitmap(3, 12, StatsQrCode);
		}

		void onUpdate()
		{

			if (_gamepad.isAnyKeyPressed())
			{
				setNextState(TetrisState::SELECT_LEVEL);
				return;
			}

		}

};
