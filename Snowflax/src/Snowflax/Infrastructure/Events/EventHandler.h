#pragma once

#include "Event.h"
#include <vector>


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {


			class IEventHandler {
			protected:
				IEventHandler() = default;
				~IEventHandler() = default;
			public:
				virtual EventType GetEventType() = 0;
				virtual bool Handle(Event&) = 0;
				virtual void Subscribe(std::function<void>) = 0;
				virtual void Unsubscribe(std::function<void>) = 0;
			};
			template<EventClass E>
			class EventHandler : IEventHandler {
			public:
				EventHandler() = default;
				~EventHandler() = default;

				virtual EventType GetEventType() override { return E::GetEventType(); }
				virtual bool Handle(Event& _e) {
					for each (std::function<void, E&> func in m_Callbacks)
					{
						if (func) func((E&)_e);
					}
				}
				virtual void Subscribe(std::function<void, E&> _func) {
					if (std::find(m_Callbacks.begin(), m_Callbacks.end(), _func) == m_Callbacks.end()) {
						m_Callbacks.push_back(_func);
					}
				}
				virtual void Unsubscribe(std::function<void, E&> _func) {
					auto pos = std::find(m_Callbacks.begin(), m_Callbacks.end(), _func) != m_Callbacks.end();
					if (pos != m_Callbacks.end()) {
						m_Callbacks.erase(pos);
					}
				}
				void operator+= (std::function<void, E&> _func) {
					Subscribe(_func);
				}
				void operator-= (std::function<void, E&> _func) {
					Unsubscribe(_func);
				}
			private:
				std::vector<std::function<void, E&>> m_Callbacks;
			};

		}
	}
}