#pragma once

#include "Event.h"


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {

			class IEventListener {
			protected:
				IEventListener() = default;
				~IEventListener() = default;
			public:
				virtual void OnEvent(Event&) = 0;
			};

		}
	}
}