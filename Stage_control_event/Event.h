#ifndef EVENT_H
#define EVENT_H

#include "stdafx.h"

namespace stage_control{
	struct Event{
		virtual unsigned int getEventType() = 0;
	};
}

#endif