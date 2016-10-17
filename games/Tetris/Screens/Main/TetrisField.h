#pragma once

#include <IDrawable.h>
#include <stdint.h>

class TetrisBlock;

class TetrisField : public IDrawable
{
	public:
		static const int COLUMNS = 10;
		static const int ROWS = 20;
		static const int POINT_WIDTH = 2;
		static const int POINT_HEIGHT = 2;
		static const unsigned FULL_ROW_MASK = 0xFFFFFFFF >> (32-COLUMNS);

		void clear();

		void setPoint(int fieldX, int fieldY, bool value);
		bool getPoint(int fieldX, int fieldY) const;

		void draw(Framebuffer& fb, int x, int y, bool doInvert=false) const override;

		bool isRowFull(int row) const;
		void deleteRow(int row);

		bool hasFullRows() const;
		int deleteFullRows();

		void setInvertFullRows(bool doInvert);

	private:
		uint16_t _data[ROWS] = { 0 };
		bool _invertFullRows = false;
};
