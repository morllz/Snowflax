#pragma once

#include "SFLXpch.h"
#include "Event.h"
#include "Snowflax/Core/Function.h"

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
		EventHandler(Args... _callbackArgs)
		requires requires (Args... _args) { Function<bool, TEvent&>(_args...); }
			: m_Callback(Function<bool, TEvent&>(_callbackArgs...)) {}

		void Handle(Event& _e) override
		{
			if(_e.GetEventType() == GetEventType()) _e.Handled() |= m_Callback(static_cast<TEvent&>(_e));
		}
		EventType GetEventType() override
		{
			return TEvent::GetStaticType();
		}
	private:
		Function<bool, TEvent&> m_Callback;
	};
}