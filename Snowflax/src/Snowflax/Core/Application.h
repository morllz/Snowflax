#pragma once

#include "Snowflax/Events/EventDispatcher.h"
#include "LayerStack.h"
#include "Snowflax/Events/WindowEvents.h"
#include "Window.h"



namespace Snowflax {


	class Application : public EventListener, EventDispatcher {
	public:
		Application();
		~Application() override = default;

		virtual void Run();
		virtual void Shutdown();
		void OnEvent(Event& _event) override;
		virtual bool IsRunning() { return m_IsRunning; }

		virtual bool OnWindowClose(WindowCloseEvent& _event);
	
	private:
		Scope<Window> m_Window;
		LayerStack m_LayerStack;

		bool m_IsRunning = false;
	};
}