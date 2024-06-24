#include "SFLXpch.h"
#include "Application.h"


Snowflax::Application::Application()
{
	Subscribe<WindowShouldCloseEvent>(&Application::OnWindowShouldClose, this);
	m_Window = Window::Create();
	m_Window->SetEventListener(this);
}

void Snowflax::Application::Run ()
{
	m_IsRunning = true;

	while (m_IsRunning)
	{
		m_Window->Update();
		m_LayerStack.Update();
	}

}

void Snowflax::Application::Shutdown() {

}

void Snowflax::Application::OnEvent(Event& _event) {
	Send(_event);
	m_LayerStack.OnEvent(_event);
}

bool Snowflax::Application::OnWindowShouldClose(WindowShouldCloseEvent& _event)
{
	m_IsRunning = false;
	return true;
}
