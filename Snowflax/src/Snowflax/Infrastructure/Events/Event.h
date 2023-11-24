#pragma once

#include "Snowflax/Core.h"
#include "EventDispatcher.h"


namespace Snowflax {

	namespace Infrastructure {

		namespace Events {

#define EVENT_CLASS_TYPE(type)	static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }
#define EVENT_CLASS_CATEGORY(category)	virtual int GetEventCategorys() const override { return category; }

#define EVENT_CLASS(name, type, category)\
			class ##name_Type_ : Event {\
			protected:\
				##name_Type_() = default;\
			public:\
				EVENT_CLASS_TYPE(type)\
				EVENT_CLASS_CATEGORY(category)\
			}\
			class ##name : ##name_Type_
#define EVENT_CLASS(name, type, category, ancestor)\
			class ##name_Type_ : ##ancestor{\
			protected:\
				##name_Type_() = default;\
			public:\
				EVENT_CLASS_TYPE(type)\
				EVENT_CLASS_CATEGORY(category)\
			}\
			class ##name : ##name_Type_
								

			enum class EventType {
				None = 0,
			};

			enum EventCategory {

			};

			class Event {
			friend EventDispatcher;
			public:
				virtual EventType GetEventType() const = 0;
				virtual int GetEventCategorys() const = 0;

				inline bool IsInCategory(EventCategory _category) { return GetEventCategorys() & _category; }
			};

			template<class T>
			concept EventClass = std::is_base_of<Event, T>::value;
		}
	}
}