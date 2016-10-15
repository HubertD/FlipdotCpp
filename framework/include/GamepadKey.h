#pragma once

class GamepadKey
{
	public:
		bool isPressed();
		bool hasDownEvent();
		bool hasUpEvent();
		bool hasPressEvent();
		bool hasRepeatEvent();

		void update(unsigned ticks);
		void update(unsigned ticks, bool isPressed);
		void resetEvents();

	private:
		static const unsigned T_FIRST_REPEAT = 200;
		static const unsigned T_REPEAT = 100;

		enum class Event {
			DOWN, UP, PRESS, REPEAT
		};

		unsigned _tNextRepeat = 0;
		unsigned _events = 0;

		void setEvent(Event event);
		bool hasEvent(Event event);
};
