#include "EventDispatcher.h"



void Snowflax::EventDispatcher::OnEvent(Event& _event)
{
	auto pos = std::ranges::find(m_EventsToListen.begin(), m_EventsToListen.end(), _event.GetEventType());
	if (pos != m_EventsToListen.end()) {
		Dispatch(_event);
	}
}

void Snowflax::EventDispatcher::Dispatch(Event& _event)
{
	for (auto it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
		auto handler = *it;
		if (handler->GetEventType() == _event.GetEventType()) handler->Handle(_event);
	}
}

void Snowflax::EventDispatcher::Register(IEventHandler& _handler)
{
	if (std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler) == m_RegisteredHandlers.end()) {
		m_RegisteredHandlers.push_back(&_handler);
	}
}

void Snowflax::EventDispatcher::Unregister(IEventHandler& _handler)
{
	auto pos = std::ranges::find(m_RegisteredHandlers.begin(), m_RegisteredHandlers.end(), &_handler);
	if (pos != m_RegisteredHandlers.end()) {
		m_RegisteredHandlers.erase(pos);
	}
}

void Snowflax::EventDispatcher::operator()(Event& _event)
{
	Dispatch(_event);
}

void Snowflax::EventDispatcher::UpdateListenedEvents()
{
	for (auto it = m_RegisteredHandlers.begin(); it < m_RegisteredHandlers.end(); it++) {
		m_EventsToListen.insert((*it)->GetEventType());
	}
}

void Snowflax::EventDispatcher::operator-=(IEventHandler& _handler)
{
	Unregister(_handler);
	m_EventsToListen.erase(_handler.GetEventType());
	UpdateListenedEvents();
}

void Snowflax::EventDispatcher::operator+=(IEventHandler& _handler)
{
	Register(_handler);
	UpdateListenedEvents();
}
