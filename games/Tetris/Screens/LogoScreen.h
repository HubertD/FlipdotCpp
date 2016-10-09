#include "../TetrisScreen.h"

#include <assets/Bitmaps.h>

class LogoScreen : public TetrisScreen
{
	public:
		using TetrisScreen::TetrisScreen;

	protected:
		static constexpr unsigned T_LOGO_MIN  = 1000;
		static constexpr unsigned T_LOGO_IDLE = 10000;

		void onEnter()
		{
			_gfx.clear();
			_gfx.drawBitmap(0, 0, BytewerkLogo, true);
		}

		void onUpdate()
		{

			if (_gamepad.isAnyKeyPressed() && (timeSinceEntered() > T_LOGO_MIN))
			{
				setNextState(TetrisState::SELECT_LEVEL);
				return;
			}

			if (timeSinceEntered() > T_LOGO_IDLE)
			{
				setNextState(TetrisState::IDLE);
			}

		}

};
