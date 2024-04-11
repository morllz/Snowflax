#pragma once

#include "EventHandler.h"
#include "IEventListener.h"
#include <unordered_set>
#include <memory>


namespace Snowflax {

			class EventDispatcher : public IEventListener {
			public:
				EventDispatcher() = default;
				~EventDispatcher() override = default;

				void OnEvent(Event& _event) override {
					auto pos = std::ranges::find(m_EventsToListen.begin(), m_EventsToListen.end(), _event.GetEventType());
					if (pos != m_EventsToListen.end()) {
						Dispatch(_event);
					}
				}

				void Dispatch(Event& _event)
				{
					for (auto it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
						auto handler = *it;
						if (handler->GetEventType() == _event.GetEventType()) handler->Handle(_event);
					}
				}

				void Register(IEventHandler& _handler) {
					if (std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler) == m_RegisteredHandlers.end()) {
						m_RegisteredHandlers.push_back(&_handler);
					}
				}
				void Unregister(IEventHandler& _handler) {
					auto pos = std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler);
					if (pos != m_RegisteredHandlers.end()) {
						m_RegisteredHandlers.erase(pos);
					}
				}

				void operator+=(IEventHandler& _handler)
				{
					Register(_handler);
					UpdateListenedEvents();
				}

				void operator-=(IEventHandler& _handler)
				{
					Unregister(_handler);
					m_EventsToListen.erase(_handler.GetEventType());
					UpdateListenedEvents();
				}

				void operator() (Event& _event) {
					Dispatch(_event);
				}
			private:
				void UpdateListenedEvents() {
					for (auto it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
						m_EventsToListen.insert((*it)->GetEventType());
					}
				}

				std::vector<IEventHandler*> m_RegisteredHandlers;
				std::unordered_set<EventType> m_EventsToListen;
			};

}