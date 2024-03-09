#pragma once

#include "Core.h"


namespace Snowflax {

	class SNOWFLAX_API Application {
	public:
		Application();
		virtual ~Application();

		virtual void Run() = 0;
		virtual void Shutdown() = 0;
	};
}