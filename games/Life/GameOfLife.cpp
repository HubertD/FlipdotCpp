#include "GameOfLife.h"

#include <FlipdotGfx.h>

GameOfLife::GameOfLife(FlipdotGfx& gfx)
  : _gfx(gfx)
{
}

GameOfLife::~GameOfLife()
{
}

void GameOfLife::init(unsigned ticks)
{
	_tNextStep = ticks + 3000;
	_gfx.drawText(1, 18, (char*)"BYTEWERK");
}

void GameOfLife::update(unsigned ticks)
{
	if (ticks>_tNextStep) {
		makeStep();
		draw();
		_tNextStep = ticks + STEP_INTERVAL;
	}
}

void GameOfLife::makeStep()
{
	for (int y=0; y<FIELD_HEIGHT; y++)
	{
		for (int x=0; x<FIELD_WIDTH; x++)
		{
			setCellState(x, y, calcNextCellState(x, y));
		}
	}
}

void GameOfLife::draw()
{
	for (int y=0; y<FIELD_HEIGHT; y++)
	{
		for (int x=0; x<FIELD_WIDTH; x++)
		{
			_gfx.setPixel(x, y, getCellState(x,y));
		}
	}
}

bool GameOfLife::getCellState(int x, int y)
{
	unsigned bit_pos = (y*FIELD_WIDTH+x);
	unsigned idx =  bit_pos / 32;
	uint32_t mask = (1 << (bit_pos % 32));
	return (_field[idx] & mask) != 0;
}

void GameOfLife::setCellState(int x, int y, bool isAlive)
{
	unsigned bit_pos = (y*FIELD_WIDTH+x);
	unsigned idx =  bit_pos / 32;
	uint32_t mask = (1 << (bit_pos % 32));
	if (isAlive)
	{
		_field[idx] |= mask;
	} else {
		_field[idx] &= ~mask;
	}
}

bool GameOfLife::getLastCellState(int x, int y)
{
	return _gfx.getPixel(x, y);
}

bool GameOfLife::calcNextCellState(int x, int y)
{
	bool isAlive = getLastCellState(x,y);
	unsigned aliveNeighbours = countLastAliveNeighbours(x, y);

	return (aliveNeighbours==3) || (isAlive && (aliveNeighbours==2));
}

unsigned GameOfLife::countLastAliveNeighbours(int x, int y)
{
	return countOneIfCellWasAlive(x-1, y-1)
		 + countOneIfCellWasAlive(x,   y-1)
		 + countOneIfCellWasAlive(x+1, y-1)
		 + countOneIfCellWasAlive(x-1, y)
		 + countOneIfCellWasAlive(x+1, y)
		 + countOneIfCellWasAlive(x-1, y+1)
		 + countOneIfCellWasAlive(x,   y+1)
		 + countOneIfCellWasAlive(x+1, y+1);
}

unsigned GameOfLife::countOneIfCellWasAlive(int x, int y)
{
	if (x<0) { x += FIELD_WIDTH; }
	if (x>=FIELD_WIDTH) { x -= FIELD_WIDTH; }
	if (y<0) { y += FIELD_HEIGHT; }
	if (y>=FIELD_HEIGHT) { y -= FIELD_HEIGHT; }

	return getLastCellState(x, y) ? 1 : 0;
}
