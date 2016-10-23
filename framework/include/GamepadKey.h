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
		static const unsigned T_DEBOUNCE = 25;
		static const unsigned T_FIRST_REPEAT = 200 - T_DEBOUNCE;
		static const unsigned T_REPEAT = 100;

		enum class Event
		{
			DOWN,
			UP,
			PRESS,
			REPEAT,
			RAW_DOWN,
			DEBOUNCED_DOWN
		};
		static const unsigned RESET_EVENT_MASK
			= (1<<(unsigned)Event::DOWN) | (1<<(unsigned)Event::UP)
			| (1<<(unsigned)Event::PRESS) | (1<<(unsigned)Event::REPEAT);

		enum class State {
			DOWN, UP
		};

		unsigned _tNextRepeat = 0;
		unsigned _tLastStateChange = 0;
		unsigned _status = 0;

		void setEvent(Event event, bool isSet);
		bool hasEvent(Event event);

		void updateDebounce(unsigned ticks, bool isPressed);
};
