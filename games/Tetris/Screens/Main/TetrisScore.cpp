#include "TetrisScore.h"

int TetrisScore::getLevel()
{
	return _level;
}

int TetrisScore::getScore()
{
	return _score;
}

int TetrisScore::getStepInterval()
{
	return _stepInterval;
}

void TetrisScore::init(int startLevel)
{
	_score = 0;
	_buf = 0;
	_destructedRows = 0;
	_startLevel = startLevel;
	_level = _startLevel;
	updateStepInterval();
}

void TetrisScore::scoreStep()
{
	_buf += (_level+1) * POINTS_PER_STEP_FACTOR;
}

void TetrisScore::scoreMerge()
{
	_score += _buf;
	_buf = 0;
}

void TetrisScore::scoreDeleteRows(int deletedRows)
{
	int factor = 0;
	switch (deletedRows)
	{
		case 1:
			factor = POINTS_1_ROW_FACTOR;
			break;
		case 2:
			factor = POINTS_2_ROWS_FACTOR;
			break;
		case 3:
			factor = POINTS_3_ROWS_FACTOR;
			break;
		case 4:
			factor = POINTS_4_ROWS_FACTOR;
			break;
	}
	_score += (_level+1) * factor;
	_destructedRows += deletedRows;
	updateLevel();
}

void TetrisScore::updateLevel()
{
	_level = (_destructedRows / ROWS_FOR_LEVEL_UP) + _startLevel;

	if(_level > MAX_LEVEL)
	{
	  _level = MAX_LEVEL;
	}

	updateStepInterval();
}

void TetrisScore::updateStepInterval() {
	_stepInterval = STEP_INTERVAL_LEVEL_0 + (_level * STEP_INTERVAL_LEVEL_DELTA);
}

