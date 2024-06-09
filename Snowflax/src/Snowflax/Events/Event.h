#pragma once


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

#define EVENT(name, type, ...) \
	class __##name##_Type_Class : public EVENT_CLASS_CALC_DERIVED(##__VA_ARGS__##, Event) { \
	protected:\
		__##name##_Type_Class() = default;\
		~__##name##_Type_Class() = default;\
	public:\
		EVENT_CLASS_TYPE(type)\
	};\
	class name : public __##name##_Type_Class
// -----------------------------------------------------------------------------------------------------------------

	enum class EventType {
		None = 0,
		DummyEvent,
		WindowClosedEvent
	};

	class Event {
	public:
		Event() = default;
		virtual ~Event() = default;

		virtual EventType GetEventType() const = 0;

		operator bool() const { return m_Handled; }
		virtual void SetHandled() { m_Handled = true; }
	private:
		bool m_Handled = false;
	};

	template<class T>
	concept EventClass = std::is_convertible_v<T*, Event*>;
	
}