#pragma once

#include "Snowflax/Core.h"
#include <string>


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {


/*

Don't ask me how this markro works, I can't recall it myself.
I've now written this abomination the second time after deleting it by accident. Was a pain in the ass and I still don't understand how it works.
To future me: DON'T DELETE THIS AGAIN AS YOU PROBABLY WON'T BE ABLE TO WRITE IT A THIRD TIME!!!!!!
*/

// ---------------------- event definition makro -------------------------------------------------------------------
#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }
#define EVENT_CLASS_CATEGORY(category, ...)	virtual int GetEventCategorys() const override { return category; }\

#define EVENT_CLASS_CALC_DERIVED(X, N, ...) N

#define EVENT(name, type, ...) \
	class SNOWFLAX_API __##name##_Type_Class : public EVENT_CLASS_CALC_DERIVED(##__VA_ARGS__##, Event) { \
	protected:\
		__##name##_Type_Class() = default;\
		~__##name##_Type_Class() = default;\
	public:\
		EVENT_CLASS_TYPE(type)\
		EVENT_CLASS_CATEGORY(##__VA_ARGS__##)\
	};\
	class SNOWFLAX_API name : public __##name##_Type_Class
// -----------------------------------------------------------------------------------------------------------------

			enum class EventType {
				None = 0,
				DummyEvent,
			};

			enum EventCategory {
				None = BIT(0),
			};

			class SNOWFLAX_API Event {
			public:
				Event() = default;
				virtual ~Event() = default;

				virtual EventType GetEventType() const = 0;
				virtual int GetEventCategorys() const = 0;

				inline bool InCategory(EventCategory _category) { return GetEventCategorys() & _category; }

			protected:
				std::string m_DebugName = "Event";
			};

			// Maybe remove this later if it creates more problems than it solves
			template<class T>
			concept EventClass = std::is_convertible_v<T*, Event*>;
		}
	}
}