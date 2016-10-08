#include <FlipdotPanel.h>

void FlipdotPanel::configure(const PanelConfig &config)
{
	_x = config.x;
	_y = config.y;
	_orientation = config.orientation;
}

inline unsigned FlipdotPanel::getRotatedColumn(unsigned column)
{
	return (_orientation == PanelOrientation::DEG_0) ? column : (ACTIVE_COLUMNS-1) - column;
}

inline unsigned FlipdotPanel::getScreenX(unsigned column)
{
	return _x + getRotatedColumn(column);
}

void FlipdotPanel::fillColumnRegister(ScreenBuffer &screen, unsigned column, uint8_t *buf)
{
	unsigned screenX = getScreenX(column);
	unsigned data = (_orientation==PanelOrientation::DEG_180)
			      ? screen.getColumnPixels(screenX, _y+19, 20, -1) << 4
			      : screen.getColumnPixels(screenX, _y,    24, +1);

	buf[0] = (data >> 0) & 0xFF;
	buf[1] = (data >> 8) & 0xFF;
	buf[2] = (data >> 16) & 0xFF;
}

bool FlipdotPanel::columnNeedsUpdate(
	unsigned column,
	FlipdotColor color,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	unsigned screenX = getScreenX(column);

	// FIXME screenbuffer y overflow at last panel, offset=16?
	return columnNeedsUpdateHelper(color, screenX, _y,    onScreenBuffer, offScreenBuffer)
		 | columnNeedsUpdateHelper(color, screenX, _y+8,  onScreenBuffer, offScreenBuffer)
		 | columnNeedsUpdateHelper(color, screenX, _y+16, onScreenBuffer, offScreenBuffer);
}

bool FlipdotPanel::columnNeedsUpdateHelper(
	FlipdotColor color,
	unsigned screenX,
	unsigned screenY,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	auto on  = onScreenBuffer.get8Pixels(screenX, screenY);
	auto off = offScreenBuffer.get8Pixels(screenX, screenY);

	if (color==FlipdotColor::BLACK)
	{
		return (on | off) != on;
	} else {
		return (on & off) != on;
	}
}

void FlipdotPanel::updateOnScreenBuffer(
	unsigned column,
	FlipdotColor color,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	unsigned screenX = getScreenX(column);
	onScreenBuffer.copyFrom(offScreenBuffer, screenX, _y, screenX, _y, 1, ACTIVE_ROWS, (color==FlipdotColor::BLACK), (color==FlipdotColor::WHITE));
}

