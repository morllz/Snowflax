#pragma once

#include "LayerStack.h"
#include "Snowflax/Events/WindowEvents.h"


namespace Snowflax {

	class Application : public EventListener, EventDispatcher {
	public:
		Application();
		~Application() override = default;

		virtual void Run();
		virtual void Shutdown();
		void OnEvent(Event& _event) override;
		virtual bool IsRunning() { return m_IsRunning; }

		virtual void OnWindowClosed(WindowClosedEvent& _event);
	
	private:
		LayerStack m_LayerStack;

		bool m_IsRunning = false;
	};
}