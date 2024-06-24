#pragma once

#include "LayerStack.h"
#include "Snowflax/Events/WindowEvents.h"
#include "Window.h"
#ifdef SFLX_PLATFORM_WINDOWS
#include "Snowflax/Platform/Windows/WindowsWindow.h"
#endif


namespace Snowflax {

	class Application : public EventListener, EventDispatcher {
	public:
		Application();
		~Application() override = default;

		virtual void Run();
		virtual void Shutdown();
		void OnEvent(Event& _event) override;
		virtual bool IsRunning() { return m_IsRunning; }

		virtual bool OnWindowShouldClose(WindowShouldCloseEvent& _event);
	
	private:
		Scope<Window> m_Window;
		LayerStack m_LayerStack;

		bool m_IsRunning = false;
	};
}