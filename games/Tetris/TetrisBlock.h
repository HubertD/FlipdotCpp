#pragma once

#include <stdint.h>
#include <FlipdotTypes.h>

class TetrisField;
class Framebuffer;

class TetrisBlock
{
	private:
		uint16_t _rotationStates[4];
		uint8_t _rotation = 0;
		int _posX = 0;
		int _posY = 0;
		static const unsigned NUMBER_OF_BLOCKS = 7;
		static TetrisBlock _blocks[NUMBER_OF_BLOCKS];

		TetrisBlock(uint16_t r1, uint16_t r2, uint16_t r3, uint16_t r4)
			: _rotationStates { r1, r2, r3, r4 }
		{
		}

	public:

		enum class Move {
			NONE,
			LEFT,
			RIGHT,
			DOWN,
			ROTATE_LEFT,
			ROTATE_RIGHT,
		};

		static TetrisBlock createRandomBlock();
		void makeMove(Move move);
		int getX();
		void setX(int newX);
		int getY();
		void setY(int newY);
		bool getPoint(int x, int y);

		bool doesCollide(TetrisField& field);
		void merge(TetrisField& field);
		void draw(Framebuffer& fb, int offsetX, int offsetY, int pointSizeX, int pointSizeY, FlipdotColor color);

};
