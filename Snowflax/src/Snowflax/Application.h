#pragma once

#include "Core.h"
#include "Events/IEventListener.h"
#include "Debug/Log.h"


namespace Snowflax {

	class Application : public IEventListener {
	public:
		Application() = default;
		~Application() override = default;

		virtual void Run();
		virtual void Shutdown();
		virtual void OnEvent(Event&);
	};
}