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
		explicit EventHandler(void(* _func)(E&)) : m_Callback(_func) {}
		template <class C, EventClass E>
		explicit EventHandler(void(C::* _func)(E&), C* _targetObj)
		{
			m_Callback = std::bind_front(_func, _targetObj);
			m_CallbackIsMember = true;
			m_TargetObj = _targetObj;
		}
		~EventHandler() override = default;

		EventType GetEventType() override
		{
			return E::GetStaticType();
		}

		void Handle(Event& _e) override
		{
			if (m_Callback) m_Callback(static_cast<E&>(_e));
		}

		std::function<void(E&)> GetCallback() const
		{
			return m_Callback;
		}
		bool IsCallbackMember() const
		{
			return m_CallbackIsMember;
		}
		void* GetTargetObject() const
		{
			return m_TargetObj;
		}

	private:
		std::function<void(E&)> m_Callback;
		bool m_CallbackIsMember = false;
		void* m_TargetObj = nullptr;
	};
}