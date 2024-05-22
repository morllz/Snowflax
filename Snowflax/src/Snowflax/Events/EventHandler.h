#pragma once

#include "SFXpch.h"
#include "Event.h"

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
		template<class C>
		EventHandler(std::function<void(const C&, E&)> _func, C* _targetObj) : m_Callback(std::bind_front(_func, _targetObj)) {}
		explicit EventHandler(std::function<void(E&)> _func) : m_Callback(_func) {}
		~EventHandler() override = default;

		void Handle(Event& _e) override
		{
			if (m_Callback) m_Callback(static_cast<E&>(_e));
		}
		EventType GetEventType() override
		{
			return E::GetStaticType();
		}
	private:
		std::function<void(E&)> m_Callback;
	};
}