#pragma once

#include "Core.h"
#include "Infrastructure/Events/IEventListener.h"


using namespace Snowflax::Infrastructure::Events;

namespace Snowflax {

	class SNOWFLAX_API Application : IEventListener {
	public:
		Application();
		virtual ~Application();

		void OnEvent(Event& _event);

		virtual void Run() = 0;
		virtual void Shutdown() = 0;
	};
}