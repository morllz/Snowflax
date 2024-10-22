#pragma once

#include "Snowflax/Core/Base.h"


namespace Snowflax
{
	class GraphicsContext
	{
	public:
		GraphicsContext() = default;
		virtual ~GraphicsContext() = default;

		virtual void Init() = 0;
		virtual void CleanUp() = 0;

		static Scope<GraphicsContext> Create();
	};
}
