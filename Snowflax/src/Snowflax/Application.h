#pragma once

#include "Layers/LayerStack.h"
#include "Debug/Log.h"
#include "Events/WindowEvents.h"


namespace Snowflax {

	class Application : public EventDispatcher, IEventListener {
	public:
		Application();
		virtual ~Application() = default;

		virtual void Run();
		virtual void Shutdown();
		void OnEvent(Event& _event) override;
		virtual bool IsRunning() { return m_IsRunning; }

		virtual void WindowClosed(WindowClosedEvent& _event);
	
	private:
		LayerStack m_LayerStack;

		bool m_IsRunning = false;
	};
}