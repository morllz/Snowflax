#pragma once

#include "Snowflax/Core.h"
#include "EventDispatcher.h"


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {



#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }
#define EVENT_CLASS_CATEGORY(category, ...)	virtual int GetEventCategorys() const override { return category; }\

#define EVENT_CLASS_CALC_DERIVED(X, N, ...) N

#define EVENT(name, type, ...) \
	class __##name##_Type_Class : EVENT_CLASS_CALC_DERIVED(##__VA_ARGS__##, Event) { \
	protected:\
		__##name##_Type_Class() = default;\
		~__##name##_Type_Class() = default;\
	public:\
		EVENT_CLASS_TYPE(type)\
		EVENT_CLASS_CATEGORY(##__VA_ARGS__##)\
	};\
	class name : public __##name##_Type_Class



			enum class EventType {
				None = 0,
			};

			enum EventCategory {
				None = BIT(0)
			};

			class Event {
			friend EventDispatcher;
			public:
				virtual EventType GetEventType() const = 0;
				virtual int GetEventCategorys() const = 0;

				inline bool InCategory(EventCategory _category) { return GetEventCategorys() & _category; }
			};

			template<class T>
			concept EventClass = std::is_base_of<Event, T>::value;
		}
	}
}