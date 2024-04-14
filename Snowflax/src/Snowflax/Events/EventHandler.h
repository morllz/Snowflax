#pragma once

#include "Event.h"
#include <vector>
#include <functional>


namespace Snowflax {

	class IEventHandler {
	protected:
		IEventHandler() = default;
		virtual ~IEventHandler() = default;
	public:
		virtual EventType GetEventType() = 0;
		virtual void Handle(Event&) = 0;
	};

	template<EventClass E>
	class EventHandler : public IEventHandler {
	public:

		explicit EventHandler(std::function<void(E&)> _func) : m_Callback(_func) {}
		~EventHandler() override = default;

		EventType GetEventType() override
		{
			return E::GetStaticType();
		}

		void Handle(Event& _e) override
		{
			if (m_Callback) m_Callback(static_cast<E&>(_e));
		}

		std::function<void(E&)> GetCallback()
		{
			return m_Callback;
		}

	private:
		std::function<void(E&)> m_Callback;
	};

}