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

		void OnEvent(Event& _event) override;

		void Dispatch(Event& _event);
		void operator() (Event& _event);

		void Register(IEventHandler& _handler);
		void Unregister(IEventHandler& _handler);
		void operator+= (IEventHandler& _handler);
		void operator-= (IEventHandler& _handler);

	private:
		void UpdateListenedEvents();

		std::vector<IEventHandler*> m_RegisteredHandlers;
		std::unordered_set<EventType> m_EventsToListen;
	};
}