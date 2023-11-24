#pragma once

#include "Event.h"
#include <vector>


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {


			class IEventHandler {
			public:
				virtual EventType GetEventType() = 0;
				virtual bool Handle(Event&) = 0;
			};
			template<EventClass E>
			class EventHandler : IEventHandler {
			public:
				virtual EventType GetEventType() override { return E::GetEventType(); }
				virtual bool Handle(Event& _e) {
					for each (std::function<void, E&> func in m_Callbacks)
					{
						if (func) func((E&)_e);
					}
				}
			private:
				std::vector<std::function<void, E&>> m_Callbacks;
			};

		}
	}
}