#pragma once

#include "Snowflax/Core/Base.h"


namespace Snowflax {

/*
Don't ask me how this macro works, I can't recall it myself.
I've now written this abomination the second time after deleting it by accident. Was a pain in the ass and I still don't understand how it works.
To future me: DON'T DELETE THIS AGAIN AS YOU PROBABLY WON'T BE ABLE TO WRITE IT A THIRD TIME!!!!!!
*/

// ---------------------- event definition macro -------------------------------------------------------------------
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }

#define EVENT_CLASS_CALC_DERIVED(X, N, ...) N

#define EVENT(name, ...) \
	class __##name##_TypeBase : public EVENT_CLASS_CALC_DERIVED(__VA_ARGS__, Event) { \
	protected:\
		__##name##_TypeBase() = default;\
		virtual ~__##name##_TypeBase() = default;\
	public:\
		EVENT_CLASS_TYPE(SFLX_MACRO_GET_FIRST_ARG(__VA_ARGS__))\
	};\
	class name : public __##name##_TypeBase
// -----------------------------------------------------------------------------------------------------------------

	enum class EventType {
		None = 0,
		DummyEvent,
		WindowShouldCloseEvent
	};

	class Event {
	public:
		Event() = default;
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;

		virtual operator bool() const { return m_Handled; }
		virtual bool& Handled() { return m_Handled; }

		virtual const char* GetName() const { return m_Name;}
		virtual std::string ToString() const  { return m_Name; }
	private:
		const char* m_Name = "Event";
		bool m_Handled = false;
	};

	template<class T>
	concept EventClass = std::is_convertible_v<T*, Event*>;
	
}