#pragma once

#include "Base.h"
#include "Snowflax/Events/EventListener.h"


namespace Snowflax
{
	struct WindowSpecs
	{
		std::string Title;
		uint32_t Width, Height;

		WindowSpecs(
			const std::string& _title = "Snowflax", 
			const uint32_t _width = 1600, 
			const uint32_t _height = 900
		) : Title(_title), Width(_width), Height(_height) {}
	};

	class Window
	{
	public:
		virtual ~Window() = default;

		virtual void Update() = 0;

		virtual uint32_t GetWidth() const = 0; 
		virtual uint32_t GetHeight() const = 0;

		virtual bool IsVSync() const = 0;
		virtual void SetVSync(bool) = 0;

		virtual void* GetNativeWindow() const = 0;

		virtual void SetEventListener(EventListener* _eventListener) = 0;

		static Scope<Window> Create(const WindowSpecs& _windowSpecs = WindowSpecs());
	};
}
