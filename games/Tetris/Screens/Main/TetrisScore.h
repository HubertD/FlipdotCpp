#pragma once

class TetrisScore
{
	private:
		static const int POINTS_1_ROW_FACTOR  =   40;
		static const int POINTS_2_ROWS_FACTOR =  100;
		static const int POINTS_3_ROWS_FACTOR =  300;
		static const int POINTS_4_ROWS_FACTOR = 1200;
		static const int POINTS_PER_STEP_FACTOR =  2;

		static const int MAX_LEVEL = 9;
		static const int ROWS_FOR_LEVEL_UP = 10;
		static const int STEP_INTERVAL_LEVEL_0 = 400;
		static const int STEP_INTERVAL_LEVEL_DELTA = -30;

		int _score = 0;
		int _buf = 0;
		int _startLevel = 0;
		int _level = 0;
		int _destructedRows = 0;
		int _stepInterval = STEP_INTERVAL_LEVEL_0;

		void updateLevel();
		void updateStepInterval();

	public:
		int getLevel();
		int getScore();
		int getStepInterval();

		void init(int startLevel);
		void scoreStep();
		void scoreMerge();
		void scoreDeleteRows(int deletedRows);

};
