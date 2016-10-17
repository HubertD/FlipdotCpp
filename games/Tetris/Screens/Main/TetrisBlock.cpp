#include <Framebuffer.h>

#include <stdlib.h>
#include "TetrisBlock.h"
#include "TetrisField.h"

TetrisBlock::BlockData TetrisBlock::_blocks[] =
{
	/*  ----  -#--
		#X##  -X--
		----  -#--
		----  -#--  */
	{ 0x0F00, 0x4444, 0x0F00, 0x4444 },

	/*  -##-  #---  ----  -#--
		#X--  #X--  -X#-  -X#-
		----  -#--  ##--  --#-
		----  ----  ----  ----  */
	{ 0x6C00, 0x8C40, 0x06C0, 0x4620 },

	/*  ----
		-##-
		-##-
		----  */
	{ 0x0660, 0x0660, 0x0660, 0x0660 },

	/*  -#-- -#-- ---- -#--
		###- -##- ###- ##--
		---- -#-- -#-- -#--
		---- ---- ---- ----  */
	{ 0x4E00, 0x4640, 0x0E40, 0x4C40 },

	/*  ##-- --#- ---- -#--
		-X#- -X#- #X-- #X--
		---- -#-- -##- #---  */
	{ 0xC600, 0x2640, 0x0C60, 0x4C80 },

	/*  -#-- #--- -##- ----
		-#-- ###- -#-- ###-
		##-- ---- -#-- --#-
		---- ---- ---- ----  */
	{ 0x44C0, 0x8E00, 0x6440, 0x0E20 },


	/*  -#-- ---- ##-- --#-
		-#-- ###- -#-- ###-
		-##- #--- -#-- ----
		---- ---- ---- ----  */
	{ 0x4460, 0x0E80, 0xC440, 0x2E00 }

};

TetrisBlock TetrisBlock::createRandomBlock()
{
	return TetrisBlock(
		rand() % NUMBER_OF_BLOCKS,
		rand() % NUMBER_OF_ROTATION_STATES
	);
}

void TetrisBlock::setPosition(int newX, int newY)
{
	_posX = newX;
	_posY = newY;
}

void TetrisBlock::move(Move theMove)
{
	switch (theMove)
	{
		case Move::LEFT:
			_posX--;
			break;
		case Move::RIGHT:
			_posX++;
			break;
		case Move::DOWN:
			_posY++;
			break;
		case Move::ROTATE_LEFT:
			_rotation = getPreviousRotationLevel();
			break;
		case Move::ROTATE_RIGHT:
			_rotation = getNextRotationLevel();
			break;
		default:
			break;
	}
}

int8_t TetrisBlock::getPreviousRotationLevel()
{
	return (_rotation>0) ? _rotation-1 : NUMBER_OF_ROTATION_STATES-1;
}

int8_t TetrisBlock::getNextRotationLevel()
{
	return (_rotation+1) % NUMBER_OF_ROTATION_STATES;
}

bool TetrisBlock::doesCollide(TetrisField& field) const
{
	for (int iy=0; iy<4; iy++)
	{
		for (int ix=0; ix<4; ix++)
		{
			if (!isPointSet(ix, iy)) { continue; }

			auto fieldX = _posX + ix;
			auto fieldY = _posY + iy;
			if ((fieldX<0)
				|| (fieldX>=TetrisField::COLUMNS)
				|| (fieldY>=TetrisField::ROWS)
				|| field.getPoint(_posX+ix, _posY+iy))
			{
				return true;
			}
		}
	}
	return false;
}

void TetrisBlock::draw(Framebuffer& fb, int offsetX, int offsetY, bool doInvert) const
{
	Rect rect = { 0, 0, POINT_SIZE_X, POINT_SIZE_Y };

	for (int iy=0; iy<HEIGHT; iy++)
	{
		for (int ix=0; ix<WIDTH; ix++)
		{
			if (!isPointSet(ix, iy)) { continue; }

			rect.x = (_posX+ix)*POINT_SIZE_X;
			rect.y = (_posY+iy)*POINT_SIZE_Y;
			fb.draw(offsetX, offsetY, rect, !doInvert);
		}
	}
}

void TetrisBlock::merge(TetrisField& field) const
{
	for (int iy=0; iy<HEIGHT; iy++)
	{
		for (int ix=0; ix<WIDTH; ix++)
		{
			if (!isPointSet(ix, iy)) { continue; }

			field.setPoint(_posX+ix, _posY+iy, true);
		}
	}
}

bool TetrisBlock::isPointSet(int x, int y) const
{
	if ((x<0) || (x>=WIDTH)) { return false; }
	if ((y<0) || (y>=HEIGHT)) { return false; }

	unsigned state = _blocks[_blockId].rotationStates[_rotation];
	unsigned row = state >> (WIDTH*y);
	unsigned mask = 1 << (WIDTH-x-1);

	return (row & mask) != 0;
}

