#pragma once

#include <queue>
#include "EventHandler.h"
#include "EventListener.h"

namespace Snowflax {

	class EventDispatcher {
	public:
		EventDispatcher() = default;

		void Send(Event& _event)
		{
			for (auto& subscribedHandler : m_SubscribedHandlers)
			{
				subscribedHandler->Handle(_event);
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
		template<EventClass TEvent, typename... Args>
		void Subscribe(Args... _callbackArgs)
		{
			m_SubscribedHandlers.insert(std::make_unique<EventHandler<TEvent>>(_callbackArgs...));
		}
		void Push(Event& _event)
		{
			m_EventQueue.push(std::ref(_event));
		}
		
	private:

		std::unordered_set<std::unique_ptr<EventHandlerBase>> m_SubscribedHandlers;
		std::queue<std::reference_wrapper<Event>> m_EventQueue;
	};

}