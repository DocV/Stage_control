#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#include "stdafx.h"
#include "Event.h"

namespace stage_control{
	class EventHandler{
	public:
		virtual void handleEvent(const Event& e) = 0;
	};
}

#endif