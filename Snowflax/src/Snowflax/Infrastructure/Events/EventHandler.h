#pragma once

#include "Event.h"
#include <vector>


namespace Snowflax {
	namespace Infrastructure {
		namespace Events {


			class SNOWFLAX_API IEventHandler {
			protected:
				IEventHandler() = default;
				virtual ~IEventHandler() = default;
			public:
				virtual EventType GetEventType() = 0;
				virtual void Handle(Event&) = 0;
			};
			template<EventClass E>
			class SNOWFLAX_API EventHandler : public IEventHandler {
			public:
				EventHandler() = default;
				~EventHandler() = default;

				virtual EventType GetEventType();
				virtual void Handle(Event& _e);
				void Subscribe(std::function<void(E&)> _func);
				void Unsubscribe(std::function<void(E&)> _func);
				void operator+= (std::function<void(E&)> _func);
				void operator-= (std::function<void(E&)> _func);

				template<EventClass E>
				void Snowflax::Infrastructure::Events::EventHandler<E>::operator()(E& _event)
				{
					Handle(_event);
				}

				void operator() (E& _event);
			private:
				std::vector<std::function<void(E&)>> m_Callbacks;
			};

		}
	}
}