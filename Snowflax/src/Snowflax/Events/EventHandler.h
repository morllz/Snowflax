#pragma once

#include "SFLXpch.h"
#include "Event.h"

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
		EventHandler(std::function<bool(TEvent&)> _func)
			: m_Callback(std::forward<std::function<bool(TEvent&)>>(_func)) {}

		void Handle(Event& _e) override
		{
			if(_e.GetEventType() == GetEventType()) _e.Handled() |= m_Callback(static_cast<TEvent&>(_e));
		}
		constexpr EventType GetEventType() override
		{
			return TEvent::GetStaticType();
		}
	private:
		std::function<bool(TEvent&)> m_Callback;
	};
}
