#pragma once

#include <IDrawable.h>
#include <stdint.h>

class TetrisField : public IDrawable
{
	public:
		void setPoint(int fieldX, int fieldY, bool value);
		bool getPoint(int fieldX, int fieldY) const;

		bool getPixel(int x, int y) const override;
		void draw(FlipdotGfx &gfx, int x, int y, bool doInvert=false) const override;

	private:
		static const int FIELD_WIDTH = 10;
		static const int FIELD_HEIGHT = 20;
		static const int POINT_WIDTH = 2;
		static const int POINT_HEIGHT = 2;

		uint16_t _data[FIELD_HEIGHT] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 0xFFFF };

		void drawPoint(FlipdotGfx &gfx, int x, int y, int fieldX, int fieldY, bool value) const;

};
