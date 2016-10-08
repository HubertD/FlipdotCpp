#include "VCDPlatform.h"

VCDPlatform::VCDPlatform()
  : _driver(*this)
{
}

void VCDPlatform::init()
{
}

void VCDPlatform::done()
{
}

void VCDPlatform::update()
{
	incrementUTicks(UTICKS_PER_UPDATE);
}

void VCDPlatform::incrementUTicks(int increment)
{
	_uticks += increment;
}

IFlipdotDriver& VCDPlatform::getFlipdotDriver()
{
	return _driver;
}

uint32_t VCDPlatform::getTicks()
{
	return _uticks / 1000;
}

bool VCDPlatform::doQuit()
{
	return (_uticksQuit>0) && (_uticks>_uticksQuit);
}

unsigned VCDPlatform::getUTicks()
{
	return _uticks;
}

void VCDPlatform::setQuitUTicks(int uticks)
{
	_uticksQuit = uticks;
}
