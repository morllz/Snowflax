#pragma once

#include "EventHandler.h"
#include "IEventListener.h"
#include <unordered_set>
#include <memory>


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {

			class SNOWFLAX_API EventDispatcher : public IEventListener {
			public:
				EventDispatcher() = default;
				~EventDispatcher() = default;

				virtual void OnEvent(Event& _event);
				void Dispatch(Event& _event);
				void Register(IEventHandler& _handler);
				void Unregister(IEventHandler& _handler);
				void operator+= (IEventHandler& _handler);
				void operator-= (IEventHandler& _handler);
				void operator() (Event& _event);
			private:
				void UpdateListenedEvents();
			private:
				std::vector<IEventHandler*> m_RegisteredHandlers;
				std::unordered_set<EventType> m_EventsToListen;
			};

		}
	}
}