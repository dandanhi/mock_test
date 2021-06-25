#pragma once

#include <map>
#include <functional>

template<typename EventType>
class EventDispatcher
{
public:
    using EventHandler = std::function<void()>;

    virtual void addEventListener(EventType eventToAdd, EventHandler handler) = 0;
    virtual void removeEventListener(EventType eventToRemove) = 0;
    virtual void dispatch(EventType eventToDispatch) = 0;
};


class EventQueue {
public:
	void EnqueueEvent(int el) {
    
  }
};
