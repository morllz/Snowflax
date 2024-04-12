#include "EventHandler.h"


using namespace Snowflax;

template<EventClass E>
void Snowflax::EventHandler<E>::Unsubscribe(std::function<void(E&)> _func)
{
	auto pos = std::ranges::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](auto f) { return f.target<void(E&)>() == _func.target<void(E&)>(); });
	if (pos != m_Callbacks.end()) m_Callbacks.erase(pos);
}

template<EventClass E>
void Snowflax::EventHandler<E>::Subscribe(std::function<void(E&)> _func)
{
	auto pos = std::ranges::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](auto f) { return f.target<void(E&)>() == _func.target<void(E&)>(); });
	if (pos == m_Callbacks.end()) m_Callbacks.push_back(_func);
}

template<EventClass E>
EventType Snowflax::EventHandler<E>::GetEventType()
{
	return E::GetStaticType();
}

template<EventClass E>
void Snowflax::EventHandler<E>::Handle(Event& _e)
{
	for (auto& func : m_Callbacks)
	{
		if (func) func(static_cast<E&>(_e));
	}
}

template<EventClass E>
void EventHandler<E>::operator+=(std::function<void(E&)> _func)
{
	Subscribe(_func);
}

template<EventClass E>
void Snowflax::EventHandler<E>::operator-=(std::function<void(E&)> _func)
{
	Unsubscribe(_func);
}

template<EventClass E>
void Snowflax::EventHandler<E>::operator()(E& _event)
{
	Handle(_event);
}
