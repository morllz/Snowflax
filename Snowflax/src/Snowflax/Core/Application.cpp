#include "SFLXpch.h"
#include "Application.h"


namespace Snowflax
{

	Application::Application()
		: EventDispatcher(SFLX_BIND_EVENT_FUNC(Application::OnWindowClose))
	{
		m_Window = Window::Create();
		m_Window->SetEventListener(this);
	}

	void Application::Run ()
	{
		m_IsRunning = true;
	
		while (m_IsRunning)
		{
			m_Window->Update();
			m_LayerStack.Update();
		}
	}

	void Application::Shutdown() {
	
	}

	void Application::OnEvent(Event& _event) {
		Send(_event);
		m_LayerStack.OnEvent(_event);
	}

	bool Application::OnWindowClose(WindowCloseEvent& _event)
	{
		m_IsRunning = false;
		return true;
	}
}

