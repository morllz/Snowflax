#pragma once

#ifdef SFLX_PLATFORM_WINDOWS

#include "GLFW/glfw3.h"
#include "Snowflax/Core/Window.h"
#include "Snowflax/Events/WindowEvents.h"

namespace Snowflax
{

	inline int GLFWWindowCount = 0;

	class WindowsWindow : public Window
	{
	public:
		WindowsWindow(const WindowSpecs& _windowSpecs);
		~WindowsWindow() override;

		void Update() override;

		uint32_t GetWidth() const override;
		uint32_t GetHeight() const override;

		bool IsVSync() const override;
		void SetVSync(bool _vsync) override;

		void* GetNativeWindow() const override;

		void SetEventListener(EventListener* _eventListener) override;

	private:
		struct WindowData
		{
			std::string Title = "Snowflax";
			uint32_t Width = 1600;
			uint32_t Height = 900;

			EventListener* EventListener = nullptr;
		};

		void SendEvent(Event& _event) const;

		WindowData m_Data;
		GLFWwindow* m_Window;

		bool m_VSync = false;

	};
}

#endif