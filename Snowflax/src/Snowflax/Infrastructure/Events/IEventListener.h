#pragma once

#include "Event.h"


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {

			class SNOWFLAX_API IEventListener {
			protected:
				IEventListener() = default;
				virtual ~IEventListener() = default;
			public:
				virtual void OnEvent(Event&) = 0;
			};

		}
	}
}