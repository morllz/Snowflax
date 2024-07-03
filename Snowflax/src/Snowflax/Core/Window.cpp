#include "SFLXpch.h"
#include "Window.h"
#ifdef SFLX_PLATFORM_WINDOWS
#include "Snowflax/Platform/Windows/WindowsWindow.h"
#endif


namespace Snowflax
{

	Scope<Window> Window::Create(const WindowSpecs& _windowSpecs)
	{
		return MakeScope<
#ifdef SFLX_PLATFORM_WINDOWS
			WindowsWindow
#else
	#error "Unknown platform!"
#endif
		>(_windowSpecs);
	}
}