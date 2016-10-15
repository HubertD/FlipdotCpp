#include <FlipdotPanel.h>

void FlipdotPanel::configure(const PanelConfig &config)
{
	_x = config.x;
	_y = config.y;
	_orientation = config.orientation;
}

inline unsigned FlipdotPanel::getRotatedColumn(unsigned column)
{
	return (_orientation == Orientation::DEG_0) ? column : (ACTIVE_COLUMNS-1) - column;
}

inline unsigned FlipdotPanel::getScreenX(unsigned column)
{
	return _x + getRotatedColumn(column);
}

void FlipdotPanel::fillShiftRegister(ScreenBuffer &screen, unsigned column, uint8_t *buf)
{
	unsigned screenX = getScreenX(column);
	unsigned data = (_orientation==Orientation::DEG_180)
			      ? screen.getColumnPixels(screenX, _y+19, 20, -1) << 4
			      : screen.getColumnPixels(screenX, _y,    24, +1);

	buf[0] = (data >> 0) & 0xF0;
	buf[1] = (data >> 8) & 0xFF;
	buf[2] = (data >> 16) & 0xFF;
}

bool FlipdotPanel::columnNeedsUpdate(
	unsigned column,
	Color color,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	unsigned screenX = getScreenX(column);

	unsigned onScreenData = onScreenBuffer.getColumnPixels(screenX, _y, 20);
	unsigned offScreenData = offScreenBuffer.getColumnPixels(screenX, _y, 20);

	if (color==Color::BLACK)
	{
		return (onScreenData | offScreenData) != onScreenData;
	} else {
		return (onScreenData & offScreenData) != onScreenData;
	}
}

void FlipdotPanel::updateOnScreenBuffer(
	unsigned column,
	Color color,
	ScreenBuffer& onScreenBuffer,
	ScreenBuffer& offScreenBuffer
)
{
	unsigned screenX = getScreenX(column);
	onScreenBuffer.copyFrom(offScreenBuffer, screenX, _y, screenX, _y, 1, ACTIVE_ROWS, (color==Color::BLACK), (color==Color::WHITE));
}

