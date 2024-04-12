#pragma once

#include "Event.h"


namespace Snowflax {

	class IEventListener {
	protected:
		IEventListener() = default;
		virtual ~IEventListener() = default;
	public:
		virtual void OnEvent(Event&) = 0;
	};
}