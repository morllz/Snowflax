#pragma once

#include "Event.h"


namespace Snowflax
{
	class WindowCloseEvent final : public Event
	{
	public:
		WindowCloseEvent() = default;

		SFLX_EVENT_CLASS_TYPE(WindowClose)
		SFLX_EVENT_CLASS_CATEGORY(WindowEvents)

		virtual const char* GetName() const override { return "WindowCloseEvent"; }
	};

	class WindowResizeEvent final : public Event
	{
	public:
		WindowResizeEvent(const int _width, const int _height)
			: m_Width(_width), m_Height(_height) {}

		SFLX_EVENT_CLASS_TYPE(WindowResize)
		SFLX_EVENT_CLASS_CATEGORY(WindowEvents)

		virtual const char* GetName() const override { return "WindowResizeEvent"; }
		virtual std::string ToString() const override { return std::format("{}(width: {}, height: {})", GetName(), m_Width, m_Height); }
	private:
		int m_Width, m_Height;
	};

	class WindowFocusEvent final : public Event
	{
	public:
		WindowFocusEvent() = default;

		SFLX_EVENT_CLASS_TYPE(WindowFocus)
		SFLX_EVENT_CLASS_CATEGORY(WindowEvents)

		virtual const char* GetName() const override { return "WindowFocusEvent"; }
	};

	class WindowLostFocusEvent final : public Event
	{
	public:
		WindowLostFocusEvent() = default;

		SFLX_EVENT_CLASS_TYPE(WindowLostFocus)
		SFLX_EVENT_CLASS_CATEGORY(WindowEvents)

		virtual const char* GetName() const override { return "WindowLostFocusEvent"; }
	};

	class WindowMovedEvent final : public Event
	{
	public:
		WindowMovedEvent(const int _xPos, const int _yPos)
			: m_XPos(_xPos), m_YPos(_yPos) {}

		SFLX_EVENT_CLASS_TYPE(WindowMoved)
		SFLX_EVENT_CLASS_CATEGORY(WindowEvents)

		virtual const char* GetName() const override { return "WindowMovedEvent"; }
		virtual std::string ToString() const override { return std::format("{}(x: {}, y: {})", GetName(), m_XPos, m_YPos); }
	private:
		int m_XPos, m_YPos;
	};

	class WindowMaximizedEvent final : public Event
	{
	public:
		WindowMaximizedEvent() = default;

		SFLX_EVENT_CLASS_TYPE(WindowMaximized)
		SFLX_EVENT_CLASS_CATEGORY(WindowEvents)

		virtual const char* GetName() const override { return "WindowMaximizedEvent"; }
	};

	class WindowMinimizedEvent final : public Event
	{
	public:
		WindowMinimizedEvent() = default;

		SFLX_EVENT_CLASS_TYPE(WindowMinimized)
		SFLX_EVENT_CLASS_CATEGORY(WindowEvents)

		virtual const char* GetName() const override { return "WindowMinimizedEvent"; }
	};
}