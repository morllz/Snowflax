#pragma once

#include "EventHandler.h"
#include "IEventListener.h"
#include <unordered_set>
#include <memory>


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {

			class EventDispatcher : public IEventListener {
			public:
				virtual void OnEvent(Event& _event) {
					auto pos = std::find(m_EventsToListen.begin(), m_EventsToListen.end(), _event.GetEventType());
					if (pos != m_EventsToListen.end()) {
						Dispatch(_event);
					}
				}
				void Dispatch(Event& _event) {
					typename std::vector<std::shared_ptr<IEventHandler>>::iterator it;
					for (it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
						(*it).get()->Handle(_event);
					}
				}
				void Register(IEventHandler& _handler) {
					auto handlerShared = std::make_shared<IEventHandler>(_handler);
					if (std::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), handlerShared) == m_RegisteredHandlers.end()) {
						m_RegisteredHandlers.push_back(handlerShared);
					}
				}
				void Unregister(IEventHandler& _handler) {
					auto handlerShared = std::make_shared<IEventHandler>(_handler);
					auto pos = std::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(),handlerShared);
					if (pos != m_RegisteredHandlers.end()) {
						m_RegisteredHandlers.erase(pos);
					}
				}
				void operator+= (IEventHandler& _handler) {
					Register(_handler);
					UpdateListenEvents();
				}
				void operator-= (IEventHandler& _handler) {
					Unregister(_handler);
					m_EventsToListen.erase(_handler.GetEventType());
					UpdateListenEvents();
				}
			private:
				void UpdateListenEvents() {
					typename std::vector<std::shared_ptr<IEventHandler>>::iterator it;
					for (it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
						m_EventsToListen.insert((*it).get()->GetEventType());
					}
				}
			private:
				std::vector<std::shared_ptr<IEventHandler>> m_RegisteredHandlers;
				std::unordered_set<EventType> m_EventsToListen;
			};

		}
	}
}