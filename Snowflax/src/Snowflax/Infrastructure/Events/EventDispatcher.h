#pragma once

#include "EventHandler.h"


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {

			class EventDispatcher {
			public:
				void Dispatch(Event&) {

				}
				void Register(IEventHandler& _handler) {
					if (std::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler) == m_RegisteredHandlers.end()) {
						m_RegisteredHandlers.push_back(&_handler);
					}
				}
				void Unregister(IEventHandler& _handler) {
					auto pos = std::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler);
					if (pos != m_RegisteredHandlers.end()) {
						m_RegisteredHandlers.erase(pos);
					}
				}
				void operator+= (IEventHandler& _handler) {
					Register(_handler);
				}
				void operator-= (IEventHandler& _handler) {
					Unregister(_handler);
				}
			private:
				std::vector<IEventHandler*> m_RegisteredHandlers;
			};

		}
	}
}