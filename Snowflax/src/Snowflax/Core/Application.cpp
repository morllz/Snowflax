#include "SFXpch.h"
#include "Application.h"


Snowflax::Application::Application()
{
	Subscribe<WindowClosedEvent>(&Application::OnWindowClosed, this);
}

void Snowflax::Application::Run ()
{
	m_IsRunning = true;

	while (m_IsRunning)
	{
		m_LayerStack.Update();
	}

}

void Snowflax::Application::Shutdown() {

}

void Snowflax::Application::OnEvent(Event& _event) {
	Send(_event);
	m_LayerStack.OnEvent(_event);
}

void Snowflax::Application::OnWindowClosed(WindowClosedEvent& _event)
{
	m_IsRunning = false;
}
