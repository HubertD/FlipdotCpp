#pragma once

#include <stdint.h>
#include <FlipdotTypes.h>
#include <IDrawable.h>

class TetrisField;
class Framebuffer;

class TetrisBlock : public IDrawable
{
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
		void setPosition(int newX, int newY);
		void move(Move theMove);
		bool wouldCollide(TetrisField& field) const;
		void merge(TetrisField& field) const;
		void draw(Framebuffer& fb, int offsetX, int offsetY, bool doInvert) const override;

	private:

		static const int NUMBER_OF_ROTATION_STATES = 4;
		struct BlockData
		{
			uint16_t rotationStates[NUMBER_OF_ROTATION_STATES];
		};

		static const unsigned NUMBER_OF_BLOCKS = 7;
		static BlockData _blocks[NUMBER_OF_BLOCKS];

		static const int WIDTH = 4;
		static const int HEIGHT = 4;
		static const int POINT_SIZE_X = 2;
		static const int POINT_SIZE_Y = 2;

		uint8_t _blockId;
		int8_t _rotation;

		int8_t _posX = 0;
		int8_t _posY = 0;

		TetrisBlock(int8_t blockId, int8_t rotation)
			: _blockId(blockId), _rotation(rotation)
		{
		}

		bool isPointSet(int x, int y) const;
		int8_t getNextRotationLevel();
		int8_t getPreviousRotationLevel();

};
