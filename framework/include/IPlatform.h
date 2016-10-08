#include <stdint.h>
#include "IFlipdotDriver.h"

class IPlatform
{
	public:
		virtual ~IPlatform() {};
		virtual void init() = 0;
		virtual void done() = 0;
		virtual void update() = 0;

		virtual IFlipdotDriver &getFlipdotDriver() = 0;
		virtual uint32_t getTicks() = 0;
		virtual bool doQuit() = 0;

};
