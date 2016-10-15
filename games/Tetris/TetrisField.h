#pragma once

#include <IDrawable.h>
#include <stdint.h>

class TetrisBlock;

class TetrisField : public IDrawable
{
	public:
		static const int FIELD_WIDTH = 10;
		static const int FIELD_HEIGHT = 20;
		static const int POINT_WIDTH = 2;
		static const int POINT_HEIGHT = 2;
		static const unsigned FULL_ROW_MASK = 0xFFFFFFFF >> (32-FIELD_WIDTH);

		void clear();

		void setPoint(int fieldX, int fieldY, bool value);
		bool getPoint(int fieldX, int fieldY) const;

		bool getPixel(int x, int y) const override;
		void draw(Framebuffer& fb, int x, int y, bool doInvert=false) const override;

		bool isRowFull(int row) const;
		void deleteRow(int row);

		bool hasFullRows() const;
		int deleteFullRows();

		void setInvertFullRows(bool doInvert);

	private:
		uint16_t _data[FIELD_HEIGHT] = { 0 };
		bool _invertFullRows = false;

		void drawPoint(Framebuffer& fb, int x, int y, int fieldX, int fieldY, bool value) const;

};
