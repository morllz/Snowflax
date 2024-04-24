#pragma once

#include "EventHandler.h"
#include "IEventListener.h"

namespace Snowflax {

	class EventDispatcher : public IEventListener {
	public:
		EventDispatcher() = default;
		~EventDispatcher() override = default;

		void OnEvent(Event& _event) override
		{
			Dispatch(_event);
		}

		void Dispatch(Event& _event)
		{
			for (auto it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); ++it) 
			{
				if (const auto handler = *it; handler->GetEventType() == _event.GetEventType()) handler->Handle(_event);
			}
		}

		void operator() (Event& _event)
		{
			Dispatch(_event);
		}

		// TODO: refactor following abomination to use less repetitive code
		template<EventClass E>
		void Subscribe(void(* _func)(E&))
		{
			auto pos = std::ranges::find_if(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(),
				[&](const std::shared_ptr<IEventHandler>& _handler)
				{
					if (_handler->GetEventType() != E::GetStaticType())
						return false;

					EventHandler<E>* handler = static_cast<EventHandler<E>*>(_handler.get());
					return !handler->IsCallbackMember()
						&& handler->GetCallback().template target<void(E&)>() == _func;
				}
			);

			if (pos == m_RegisteredHandlers.end()) {
				Register(std::make_shared<EventHandler<E>>(_func));
			}
		}
		template<EventClass E, class C>
		void Subscribe(void(C::* _func)(E&), C* _targetObj)
		{
			auto pos = std::ranges::find_if(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(),
				[&](const std::shared_ptr<IEventHandler>& _handler)
				{
					if (_handler->GetEventType() != E::GetStaticType())
						return false;

					EventHandler<E>* handler = static_cast<EventHandler<E>*>(_handler.get());
					return handler->IsCallbackMember()
						&& *handler->GetCallback().template target<void(C::*)(E&)>() == _func
						&& handler->GetTargetObject() == static_cast<void*>(_targetObj);
				}
			);

			if (pos == m_RegisteredHandlers.end()) {
				Register(std::make_shared<EventHandler<E>>(_func, _targetObj));
			}
		}
		template<EventClass E>
		void Unsubscribe(void(*_func)(E&))
		{
			auto pos = std::ranges::find_if(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(),
				[&](const std::shared_ptr<IEventHandler>& _handler)
				{
					if (_handler->GetEventType() != E::GetStaticType())
						return false;

					EventHandler<E>* handler = static_cast<EventHandler<E>*>(_handler.get());
					return !handler->IsCallbackMember()
						&& handler->GetCallback().template target<void(E&)>() == _func;
				}
			);

			if (pos != m_RegisteredHandlers.end()) {
				Unregister(*pos);
			}
		}
		template<EventClass E, class C>
		void Unsubscribe(void(C::* _func)(E&), C* _targetObj)
		{
			auto pos = std::ranges::find_if(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(),
				[&](const std::shared_ptr<IEventHandler>& _handler)
				{
					if (_handler->GetEventType() != E::GetStaticType())
						return false;

					EventHandler<E>* handler = static_cast<EventHandler<E>*>(_handler.get());
					return handler->IsCallbackMember()
						&& *handler->GetCallback().template target<void(C::*)(E&)>() == _func
						&& handler->GetTargetObject() == static_cast<void*>(_targetObj);
				}
			);

			if (pos != m_RegisteredHandlers.end()) {
				Unregister(*pos);
			}
		}
		

	private:
		void Register(const std::shared_ptr<IEventHandler>& _handler)
		{
			if (std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), _handler) == m_RegisteredHandlers.end()) {
				m_RegisteredHandlers.push_back(_handler);
			}
		}

		void Unregister(const std::shared_ptr<IEventHandler>& _handler)
		{
			auto pos = std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), _handler);
			if (pos != m_RegisteredHandlers.end()) {
				m_RegisteredHandlers.erase(pos);
			}
		}

		std::vector<std::shared_ptr<IEventHandler>> m_RegisteredHandlers;
	};

}