#pragma once

#include "Core.h"


namespace Snowflax {

	class SNOWFLAX_API Application {
	public:
		Application();
		virtual ~Application();

		void Run();
		void Shutdown();
	};
}