#pragma once

#include "SFXpch.h"
#include "Event.h"
#include "Snowflax/Utils/Function.h"

namespace Snowflax {

	class EventHandlerBase {
	protected:
		EventHandlerBase() = default;
	public:
		virtual ~EventHandlerBase() = default;
		virtual EventType GetEventType() = 0;
		virtual void Handle(Event&) = 0;
	};

	template<EventClass TEvent>
	class EventHandler : public EventHandlerBase {
	public:
		template<typename... Args>
		EventHandler(Args... _callbackArgs) : m_Callback(_callbackArgs...){ }

		void Handle(Event& _e) override
		{
			if(_e.GetEventType() == GetEventType()) m_Callback(dynamic_cast<TEvent&>(_e));
		}
		EventType GetEventType() override
		{
			return TEvent::GetStaticType();
		}
	private:
		Function<void, TEvent&> m_Callback;
	};
}