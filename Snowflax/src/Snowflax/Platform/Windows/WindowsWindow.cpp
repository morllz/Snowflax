#include "SFLXpch.h"
#include "WindowsWindow.h"


namespace Snowflax
{
	inline std::string GetGLFWError()
	{
		const char* description;
		const int code = glfwGetError(&description);
		if(description)
			return std::format("Error Code: {} Description: {}", code, description);
		else
			return "";
	}

	WindowsWindow::WindowsWindow(const WindowSpecs& _windowSpecs)
	{
		m_Data = { _windowSpecs.Title, _windowSpecs.Width, _windowSpecs.Height, nullptr};

		glfwSetErrorCallback([](int _errorCode, const char* _description)
		{
			SFLX_LOG_ERROR("GLFW error {0} occured! {1}", _errorCode, _description)
		});

		if(GLFWWindowCount == 0)
			SFLX_ASSERT(glfwInit())

		m_Window = glfwCreateWindow(
			static_cast<int>(_windowSpecs.Width), 
			static_cast<int>(_windowSpecs.Height), 
			_windowSpecs.Title.c_str(), 
			nullptr, 
			nullptr
		);
		SFLX_ASSERT(m_Window)
		GLFWWindowCount++;

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* _window)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			WindowShouldCloseEvent event;
			data->EventListener->OnEvent(event);
		});
	}

	WindowsWindow::~WindowsWindow()
	{
		glfwDestroyWindow(m_Window);
		GLFWWindowCount--;

		if(GLFWWindowCount == 0)
			glfwTerminate();
	}

	void WindowsWindow::Update()
	{
		glfwSwapBuffers(m_Window);
		glfwPollEvents();
	}

	uint32_t WindowsWindow::GetWidth() const
	{
		return m_Data.Width;
	}

	uint32_t WindowsWindow::GetHeight() const
	{
		return m_Data.Height;
	}

	bool WindowsWindow::IsVSync() const
	{
		return m_VSync;
	}

	void WindowsWindow::SetVSync(bool _vsync)
	{
		if(_vsync != m_VSync)
		{
			glfwSwapInterval(_vsync);
			m_VSync = _vsync;
		}
	}


	void* WindowsWindow::GetNativeWindow() const
	{
		return m_Window;
	}
	void WindowsWindow::SetEventListener(EventListener* _eventListener)
	{
		m_Data.EventListener = _eventListener;
	}

	void WindowsWindow::SendEvent(Event& _event) const
	{
		m_Data.EventListener->OnEvent(_event);
	}
}