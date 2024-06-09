#pragma once

#include "Event.h"


namespace Snowflax {

	class EventListener {
	protected:
		EventListener() = default;
		virtual ~EventListener() = default;
	public:
		virtual void OnEvent(Event&) = 0;
	};
}