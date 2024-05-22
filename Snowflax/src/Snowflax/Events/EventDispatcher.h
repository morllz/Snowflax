#pragma once

#include <queue>
#include "EventHandler.h"
#include "IEventListener.h"

namespace Snowflax {

	class EventDispatcher {
	public:
		EventDispatcher() = default;

		void Send(Event& _event)
		{
			for (auto& subscribedHandler : m_SubscribedHandlers)
			{
				if(subscribedHandler->GetEventType() == _event.GetEventType())subscribedHandler->Handle(_event);
			}
		}
		void SendAll()
		{
			while (!m_EventQueue.empty()) 
			{
				Send(m_EventQueue.front());
				m_EventQueue.pop();
			}
		}
		template<EventClass E>
		void Subscribe(std::function<void(E&)> _func)
		{
			m_SubscribedHandlers.insert(std::make_shared<EventHandler<E>>(_func));
		}
		template<EventClass E, typename C>
		void Subscribe(std::function<void(const C&, E&)> _func, C* _targetObj)
		{
			Subscribe(std::bind_front(_func, _targetObj));
		}
		void Push(Event& _event)
		{
			m_EventQueue.push(std::ref(_event));
		}
		
	private:

		std::unordered_set<std::shared_ptr<IEventHandler>> m_SubscribedHandlers;
		std::queue<std::reference_wrapper<Event>> m_EventQueue;
	};

}