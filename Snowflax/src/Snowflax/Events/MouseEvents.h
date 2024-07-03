#pragma once

#include "Event.h"
#include "Snowflax/Core/MouseCodes.h"

namespace Snowflax
{
	class MouseButtonPressedEvent final : public Event
	{
	public:
		MouseButtonPressedEvent(const Mouse::MouseCode _mouseCode)
			: m_MouseCode(_mouseCode) {}

		SFLX_EVENT_CLASS_TYPE(MouseButtonPressed)
		SFLX_EVENT_CLASS_CATEGORY(InputEvents | MouseEvents)

		virtual const char* GetName() const override { return "MouseButtonPressedEvent"; }
		virtual std::string ToString() const override
		{
			std::string buttonName;
			switch (m_MouseCode)
			{
			case Mouse::Button0:
				buttonName = "MouseButton0 / MouseButtonLeft";
				break;
			case Mouse::Button1:
				buttonName = "MouseButton1 / MouseButtonRight";
				break;
			case Mouse::Button2:
				buttonName = "MouseButton2 / MouseButtonMiddle";
				break;
			case Mouse::Button3:
				buttonName = "MouseButton3";
				break;
			case Mouse::Button4:
				buttonName = "MouseButton4";
				break;
			case Mouse::Button5:
				buttonName = "MouseButton5";
				break;
			case Mouse::Button6:
				buttonName = "MouseButton6";
				break;
			case Mouse::Button7:
				buttonName = "MouseButton7";
				break;
			}
			return std::format(
				"{}(mouse code: {}, readable: '{}')", 
				GetName(), static_cast<int>(m_MouseCode), buttonName
			);
		}
	private:
		Mouse::MouseCode m_MouseCode;
	};

	class MouseButtonReleasedEvent final : public Event
	{
	public:
		MouseButtonReleasedEvent(const Mouse::MouseCode _mouseCode)
			: m_MouseCode(_mouseCode) {}

		SFLX_EVENT_CLASS_TYPE(MouseButtonReleased)
		SFLX_EVENT_CLASS_CATEGORY(InputEvents | MouseEvents)

		virtual const char* GetName() const override { return "MouseButtonReleasedEvent"; }
		virtual std::string ToString() const override
		{
			std::string buttonName;
			switch (m_MouseCode)
			{
			case Mouse::Button0:
				buttonName = "MouseButton0 / MouseButtonLeft";
				break;
			case Mouse::Button1:
				buttonName = "MouseButton1 / MouseButtonRight";
				break;
			case Mouse::Button2:
				buttonName = "MouseButton2 / MouseButtonMiddle";
				break;
			case Mouse::Button3:
				buttonName = "MouseButton3";
				break;
			case Mouse::Button4:
				buttonName = "MouseButton4";
				break;
			case Mouse::Button5:
				buttonName = "MouseButton5";
				break;
			case Mouse::Button6:
				buttonName = "MouseButton6";
				break;
			case Mouse::Button7:
				buttonName = "MouseButton7";
				break;
			}
			return std::format(
				"{}(mouse code: {}, readable: '{}')", 
				GetName(), static_cast<int>(m_MouseCode), buttonName
			);
		}
	private:
		Mouse::MouseCode m_MouseCode;
	};

	class MouseScrolledEvent final : public Event
	{
	public:
		MouseScrolledEvent(const float _xOffset, const float _yOffset)
			: m_XOffset(_xOffset), m_YOffset(_yOffset) {}

		SFLX_EVENT_CLASS_TYPE(MouseScrolled)
		SFLX_EVENT_CLASS_CATEGORY(InputEvents | MouseEvents)

		const char* GetName() const override { return "MouseScrolledEvent"; }
		std::string ToString() const override
		{
			return std::format(
			"{}(X offset: {}, Y offset: {})",
				GetName(), m_XOffset, m_YOffset
			);
		}
	private:
		float m_XOffset, m_YOffset;
	};

	class MouseMovedEvent final : public Event
	{
	public:
		MouseMovedEvent(const float _xPos, const float _yPos)
			: m_XPos(_xPos), m_YPos(_yPos) {}

		SFLX_EVENT_CLASS_TYPE(MouseMoved)
		SFLX_EVENT_CLASS_CATEGORY(InputEvents | MouseEvents)

		virtual const char* GetName() const override { return "MouseMovedEvent"; }
		virtual std::string ToString() const override { return std::format("{}(x: {}, y: {})", GetName(), m_XPos, m_YPos); }
	private:
		float m_XPos, m_YPos;
	};
}
