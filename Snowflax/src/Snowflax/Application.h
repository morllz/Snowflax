#pragma once

#include "Layers/LayerStack.h"
#include "Debug/Log.h"


namespace Snowflax {

	class Application : public EventDispatcher {
	public:
		Application() = default;
		~Application() override = default;

		virtual void Run();
		virtual void Shutdown();
		void OnEvent(Event& _event) override;
		virtual bool IsRunning() { return m_IsRunning; }
	
	private:
		LayerStack m_LayerStack;

		bool m_IsRunning = false;
	};
}