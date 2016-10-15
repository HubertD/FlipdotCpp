#pragma once

#include <stdint.h>
#include <IGame.h>

class Environment;

class GameOfLife : public IGame
{
	public:
		GameOfLife(Environment& env);
		virtual ~GameOfLife();
		void init(unsigned ticks) override;
		void update(unsigned ticks) override;

	private:
		static const int FIELD_WIDTH = 32;
		static const int FIELD_HEIGHT = 40;
		static const int STEP_INTERVAL = 500;
		static const unsigned FIELD_ARRAY_LENGTH = (FIELD_WIDTH * FIELD_HEIGHT - 1)/32 + 1;

		Environment& _env;
		uint32_t _field[FIELD_ARRAY_LENGTH] = { 0 };
		unsigned _tNextStep = 0;

		void makeStep();
		void draw();

		bool getCellState(int x, int y);
		void setCellState(int x, int y, bool isAlive);
		bool getLastCellState(int x, int y);
		bool calcNextCellState(int x, int y);
		unsigned countOneIfCellWasAlive(int x, int y);
		unsigned countLastAliveNeighbours(int x, int y);

};
