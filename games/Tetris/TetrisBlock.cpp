#include <games/Tetris/TetrisBlock.h>

#include <games/Tetris/TetrisField.h>
#include <FlipdotGfx.h>
#include <stdlib.h>

TetrisBlock TetrisBlock::_blocks[] =
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
	int x = rand();
	x %= NUMBER_OF_BLOCKS;
	return _blocks[x];
}

void TetrisBlock::setX(int newX)
{
	_posX = newX;
}

void TetrisBlock::setY(int newY)
{
	_posY = newY;
}

void TetrisBlock::draw(FlipdotGfx& gfx, int offsetX, int offsetY, int pointSizeX, int pointSizeY, FlipdotColor color)
{
	auto px = offsetX + pointSizeX * _posX;
	auto py = offsetY + pointSizeY * _posY;

	for (int iy=0; iy<4; iy++)
	{
		for (int ix=0; ix<4; ix++)
		{
			if (getPoint(ix, iy))
			{
				gfx.drawRect(px+pointSizeX*ix, py+pointSizeY*iy, pointSizeX, pointSizeY, color==FlipdotColor::BLACK);
			}
		}
	}

}

void TetrisBlock::merge(TetrisField& field)
{
	for (int iy=0; iy<4; iy++)
	{
		for (int ix=0; ix<4; ix++)
		{
			if (getPoint(ix, iy))
			{
				field.setPoint(_posX+ix, _posY+iy, true);
			}
		}
	}
}

bool TetrisBlock::getPoint(int x, int y)
{
	if ((x<0) || (x>3)) { return false; }
	if ((y<0) || (y>3)) { return false; }

	unsigned state = _rotationStates[_rotation];
	unsigned row = state >> (4*y);
	unsigned mask = (1<<3) >> x;

	return (row & mask) != 0;
}

int TetrisBlock::getX()
{
	return _posX;
}

int TetrisBlock::getY()
{
	return _posY;
}

bool TetrisBlock::doesCollide(TetrisField& field)
{
	for (int iy=0; iy<4; iy++)
	{
		for (int ix=0; ix<4; ix++)
		{
			if (getPoint(ix, iy))
			{
				auto fieldX = _posX + ix;
				auto fieldY = _posY + iy;
				if ((fieldX<0)
					|| (fieldX>=TetrisField::FIELD_WIDTH)
					|| (fieldY>=TetrisField::FIELD_HEIGHT)
					|| field.getPoint(_posX+ix, _posY+iy))
				{
					return true;
				}
			}
		}
	}
	return false;
}

void TetrisBlock::makeMove(Move move)
{
	switch (move)
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
			_rotation = (_rotation <= 0) ? 3 : _rotation-1;
			break;
		case Move::ROTATE_RIGHT:
			_rotation = (_rotation >= 3) ? 0 : _rotation+1;
			break;
		default:
			break;
	}
}
