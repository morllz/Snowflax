#include "SFLXpch.h"
#include "GraphicsContext.h"
#include "Snowflax/Platform/Vulkan/VulkanContext.h"


namespace Snowflax
{
	Scope<GraphicsContext> GraphicsContext::Create(Window* _window) {
		return MakeScope<VulkanContext>(_window);
	}

}
