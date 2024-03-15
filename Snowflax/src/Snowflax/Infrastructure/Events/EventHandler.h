#pragma once

#include "Event.h"
#include <vector>


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {


			class SNOWFLAX_API IEventHandler {
			protected:
				IEventHandler() = default;
				virtual ~IEventHandler() = default;
			public:
				virtual EventType GetEventType() = 0;
				virtual void Handle(Event&) = 0;
			};
			template<EventClass E>
			class SNOWFLAX_API EventHandler : public IEventHandler {
			public:
				EventHandler() = default;
				~EventHandler() = default;

				virtual EventType GetEventType() { return E::GetStaticType(); }
				virtual void Handle(Event& _e) {
					for  (auto& func : m_Callbacks)
					{
						if(func) func(static_cast<E&>(_e));
					}
				}
				void Subscribe(std::function<void(E&)> _func) {
					auto pos = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](auto f) { return f.target<void(E&)>() == _func.target<void(E&)>(); });
					if (pos == m_Callbacks.end()) m_Callbacks.push_back(_func);
				}
				void Unsubscribe(std::function<void(E&)> _func) {
					auto pos = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](auto f) { return f.target<void(E&)>() == _func.target<void(E&)>(); });
					if (pos != m_Callbacks.end()) m_Callbacks.erase(pos);
				}
				void operator+= (std::function<void(E&)> _func) {
					Subscribe(_func);
				}
				void operator-= (std::function<void(E&)> _func) {
					Unsubscribe(_func);
				}
				void operator() (E& _event) {
					Handle(_event);
				}
			private:
				std::vector<std::function<void(E&)>> m_Callbacks;
			};

		}
	}
}