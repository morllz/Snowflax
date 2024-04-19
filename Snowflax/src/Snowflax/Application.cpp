#include "SFXpch.h"
#include "Application.h"


Snowflax::Application::Application()
{
	Subscribe<WindowClosedEvent, Application>(&Application::WindowClosed, this);
}

void Snowflax::Application::Run ()
{
	m_IsRunning = true;

	while (m_IsRunning)
	{
		m_LayerStack.Update();
		SFX_LOG_INFO("bobo");
	}

}

void Snowflax::Application::Shutdown() {

}

void Snowflax::Application::OnEvent(Event& _event) {
	Dispatch(_event);
	m_LayerStack.OnEvent(_event);
}

void Snowflax::Application::WindowClosed(WindowClosedEvent& _event)
{

}
