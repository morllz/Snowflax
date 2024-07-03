#include "SFLXpch.h"
#include "WindowsWindow.h"

#include "Snowflax/Events/KeyEvents.h"
#include "Snowflax/Events/MouseEvents.h"


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
			SFLX_LOG_ERROR("GLFW error {0} occured! {1}", _errorCode, _description);
		});

		if(GLFWWindowCount == 0)
			SFLX_ASSERT(glfwInit());

		m_Window = glfwCreateWindow(
			static_cast<int>(_windowSpecs.Width), 
			static_cast<int>(_windowSpecs.Height), 
			_windowSpecs.Title.c_str(), 
			nullptr, 
			nullptr
		);
		SFLX_ASSERT(m_Window);
		GLFWWindowCount++;

		glfwSetWindowUserPointer(m_Window, &m_Data);

		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* _window)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			WindowCloseEvent event;
			data->EventListener->OnEvent(event);
		});

		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* _window, int _width, int _height)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			WindowResizeEvent event(_width, _height);
			data->EventListener->OnEvent(event);
		});

		glfwSetWindowPosCallback(m_Window, [](GLFWwindow* _window, int _xPos, int _yPos)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			WindowMovedEvent event(_xPos, _yPos);
			data->EventListener->OnEvent(event);
		});
		glfwSetWindowFocusCallback(m_Window, [](GLFWwindow* _window, int _focus)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			if(_focus)
			{
				WindowFocusEvent event;
				data->EventListener->OnEvent(event);
			}
			else
			{
				WindowLostFocusEvent event;
				data->EventListener->OnEvent(event);
			}
		});

		glfwSetWindowMaximizeCallback(m_Window, [](GLFWwindow* _window, int _maximized)
		{
			if(!_maximized) return;
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			WindowMaximizedEvent event;
			data->EventListener->OnEvent(event);
		});

		glfwSetWindowIconifyCallback(m_Window, [](GLFWwindow* _window, int _iconified)
		{
			if(!_iconified) return;
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			WindowMinimizedEvent event;
			data->EventListener->OnEvent(event);
		});

		glfwSetKeyCallback(m_Window, [](GLFWwindow* _window, int _keyCode, int _scanCode, int _action, int _modFlags)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			switch (_action)
			{
			case GLFW_PRESS:
				{
					KeyPressedEvent event(static_cast<Key::KeyCode>(_keyCode), _modFlags, 0);
					data->EventListener->OnEvent(event);
					break;
				}
			case GLFW_RELEASE:
				{
					KeyReleasedEvent event(static_cast<Key::KeyCode>(_keyCode), _modFlags);
					data->EventListener->OnEvent(event);
					break;
				}
			case GLFW_REPEAT:
				{
					KeyPressedEvent event(static_cast<Key::KeyCode>(_keyCode), _modFlags, 1);
					data->EventListener->OnEvent(event);
					break;
				}
			default:
				break;
			}
		});

		glfwSetCharCallback(m_Window, [](GLFWwindow* _window, unsigned int _keyCode)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			KeyTypedEvent event(static_cast<Key::KeyCode>(_keyCode));
			data->EventListener->OnEvent(event);
		});

		glfwSetScrollCallback(m_Window, [](GLFWwindow* _window, double _xOffset, double _yOffset)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			MouseScrolledEvent event(static_cast<float>(_xOffset), static_cast<float>(_yOffset));
			data->EventListener->OnEvent(event);
		});

		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* _window, double _xPos, double _yPos)
		{
			WindowData* data = static_cast<WindowData*>(glfwGetWindowUserPointer(_window));
			MouseMovedEvent event(static_cast<float>(_xPos), static_cast<float>(_yPos));
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
