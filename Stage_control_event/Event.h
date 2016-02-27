#ifndef EVENT_H
#define EVENT_H

#include "stdafx.h"

namespace stage_control{
	/** Tapahtumajärjestelmän viestien abstrakti yliluokka*/
	struct Event{
		/** Hakee viestin tyyppitunnuksen
		@param tyyppitunnus
		*/
		virtual unsigned int getEventType() const = 0;
	};
}
#endif