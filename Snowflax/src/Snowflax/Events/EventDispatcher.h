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

		void OnEvent(Event& _event) override
		{
			Dispatch(_event);
		}

		void Dispatch(Event& _event)
		{
			for (auto it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
				auto handler = *it;
				if (handler->GetEventType() == _event.GetEventType()) handler->Handle(_event);
			}
		}

		void operator() (Event& _event)
		{
			Dispatch(_event);
		}

		template<EventClass E>
		void Subscribe(std::function<void(E&)> _func)
		{
			auto pos = std::ranges::find_if(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(),
				[&](IEventHandler* handler) 
				{ 
					return handler->GetEventType() == E::GetStaticType() && 
						((EventHandler<E>*)handler)->GetCallback().target<void(E&)>() == _func.target<void(E&)>(); 
				}
			);

			if (pos == m_RegisteredHandlers.end()) {
				Register(new EventHandler<E>(_func));
			}
		}

		template<EventClass E>
		void Unsubscribe(std::function<void(E&)> _func)
		{
			auto pos = std::ranges::find_if(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), 
				[&](IEventHandler* handler) 
				{ 
					return handler->GetEventType() == E::GetStaticType() && 
						((EventHandler<E>*)handler)->GetCallback().target<void(E&)>() == _func.target<void(E&)>(); 
				}
			);

			if (pos != m_RegisteredHandlers.end()) {
				Unregister(*pos);
			}
		}

		void Register(IEventHandler* _handler)
		{
			if (std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), _handler) == m_RegisteredHandlers.end()) {
				m_RegisteredHandlers.push_back(_handler);
			}
		}

		void Unregister(IEventHandler* _handler)
		{
			auto pos = std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), _handler);
			if (pos != m_RegisteredHandlers.end()) {
				m_RegisteredHandlers.erase(pos);
			}
		}

	private:

		std::vector<IEventHandler*> m_RegisteredHandlers;
	};

}