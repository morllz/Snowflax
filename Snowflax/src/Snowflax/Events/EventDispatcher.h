#pragma once

#include <queue>
#include "EventHandler.h"
#include "EventListener.h"

namespace Snowflax {

	class EventDispatcher {
	public:
		EventDispatcher() = default;

		void Send(Event& _event) const
		{
			for (auto& subscribedHandler : m_SubscribedHandlers)
			{
				subscribedHandler->Handle(_event);
			}
		}
		template<EventClass TEvent, typename... Args>
		void Subscribe(Args... _callbackArgs)
		{
			m_SubscribedHandlers.insert(std::make_unique<EventHandler<TEvent>>(_callbackArgs...));
		}
		
	private:

		std::unordered_set<std::unique_ptr<EventHandlerBase>> m_SubscribedHandlers;
	};

}