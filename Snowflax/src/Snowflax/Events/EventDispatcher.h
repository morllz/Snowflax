#pragma once

#include "EventHandler.h"
#include "EventListener.h"
#include "Snowflax/Core/Base.h"

#define SFLX_BIND_EVENT_FUNC(func) BindEventFunc(&##func, this)

namespace Snowflax {

    template<EventClass TEvent, typename T>
    constexpr std::function<bool(TEvent&)> BindEventFunc(bool(T::* _func)(TEvent&), T* _instance)
    {
	    return std::bind_front(_func, _instance);
    }

    class EventDispatcher {
    public:
        EventDispatcher() = default;
        template<EventClass... TEvents>
        EventDispatcher(std::function<bool(TEvents&)>... _funcs)
        {
	        (Subscribe(_funcs), ...);
        }
        virtual ~EventDispatcher() = default;

        void Send(Event& _event) const
        {;
            for (auto& subscribedHandler : m_SubscribedHandlers)
            {
                subscribedHandler->Handle(_event);
            }
        }

        template<EventClass TEvent>
        void Subscribe(std::function<bool(TEvent&)> _func)
        {
            m_SubscribedHandlers.insert(MakeScope<EventHandler<TEvent>>(std::forward<std::function<bool(TEvent&)>>(_func)));
        }

    private:
        std::unordered_set<Scope<EventHandlerBase>> m_SubscribedHandlers;
    };

}