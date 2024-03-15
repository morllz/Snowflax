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

				virtual void OnEvent(Event& _event) {
					auto pos = std::find(m_EventsToListen.begin(), m_EventsToListen.end(), _event.GetEventType());
					if (pos != m_EventsToListen.end()) {
						Dispatch(_event);
					}
				}
				void Dispatch(Event& _event) {
					typename std::vector<IEventHandler*>::iterator it;
					for (it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
						auto handler = *it;
						if (handler->GetEventType() == _event.GetEventType()) handler->Handle(_event);
					}
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
					UpdateListenedEvents();
				}
				void operator-= (IEventHandler& _handler) {
					Unregister(_handler);
					m_EventsToListen.erase(_handler.GetEventType());
					UpdateListenedEvents();
				}
				void operator() (Event& _event) {
					Dispatch(_event);
				}
			private:
				void UpdateListenedEvents() {
					typename std::vector<IEventHandler*>::iterator it;
					for (it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
						m_EventsToListen.insert((*it)->GetEventType());
					}
				}
			private:
				std::vector<IEventHandler*> m_RegisteredHandlers;
				std::unordered_set<EventType> m_EventsToListen;
			};

		}
	}
}