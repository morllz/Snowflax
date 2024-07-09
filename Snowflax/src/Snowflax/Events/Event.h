#pragma once

#include "Snowflax/Core/Base.h"


namespace Snowflax {

#define SFLX_EVENT_CLASS_TYPE(type)	constexpr static EventType GetStaticType() { return EventType::type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }
#define SFLX_EVENT_CLASS_CATEGORY(...) virtual int GetCategoryTags() const { return __VA_ARGS__; }

	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved, WindowMaximized, WindowMinimized,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved
	};
	enum EventCategory
	{
		None = BIT(0),
		WindowEvents = BIT(1),
		InputEvents = BIT(2),
		KeyEvents = BIT(3),
		MouseEvents = BIT(4)
	};

    class Event {
    public:
        Event() = default;
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual int GetCategoryTags() const = 0;
        virtual bool InCategory(int _category)
        {
            return GetCategoryTags() & _category;
        }

        virtual operator bool() const { return m_Handled; }
        virtual bool& Handled() { return m_Handled; }

        virtual const char* GetName() const { return "Event"; }
        virtual std::string ToString() const { return GetName(); }

    private:
        bool m_Handled = false;
    };

	inline std::ostream& operator<<(std::ostream& _os, const Event& _e)
	{
		return _os << _e.ToString();
	}

	template<class T>
	concept EventClass = std::is_convertible_v<T*, Event*>;
	
}