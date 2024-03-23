#include "EventHandler.h"

using namespace Snowflax::Infrastructure::Events;


template<EventClass E>
EventType Snowflax::Infrastructure::Events::EventHandler<E>::GetEventType()
{
	return E::GetStaticType();
}

template<EventClass E>
void Snowflax::Infrastructure::Events::EventHandler<E>::Handle(Event& _e)
{
	for (auto& func : m_Callbacks)
	{
		if (func) func(static_cast<E&>(_e));
	}
}

template<EventClass E>
void Snowflax::Infrastructure::Events::EventHandler<E>::Subscribe(std::function<void(E&)> _func)
{
	auto pos = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](auto f) { return f.target<void(E&)>() == _func.target<void(E&)>(); });
	if (pos == m_Callbacks.end()) m_Callbacks.push_back(_func);
}

template<EventClass E>
void Snowflax::Infrastructure::Events::EventHandler<E>::Unsubscribe(std::function<void(E&)> _func)
{
	auto pos = std::find_if(m_Callbacks.begin(), m_Callbacks.end(), [&](auto f) { return f.target<void(E&)>() == _func.target<void(E&)>(); });
	if (pos != m_Callbacks.end()) m_Callbacks.erase(pos);
}

template<EventClass E>
void Snowflax::Infrastructure::Events::EventHandler<E>::operator+=(std::function<void(E&)> _func)
{
	Subscribe(_func);
}

template<EventClass E>
void Snowflax::Infrastructure::Events::EventHandler<E>::operator-=(std::function<void(E&)> _func)
{
	Unsubscribe(_func);
}