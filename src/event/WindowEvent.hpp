#ifndef _EVENT_WINDOWEVENT_HPP
#define _EVENT_WINDOWEVENT_HPP

#include "Event.hpp"

#include <glm/glm.hpp>

class WindowEvent : public Event {
public:
    WindowEvent(Type _type) : Event(_type) {}
};

class WindowResizeEvent : public WindowEvent {
public:
    WindowResizeEvent() : WindowEvent(Event::WindowResize) {}
    int width, height;
};

class WindowCloseEvent : public WindowEvent {
public:
    WindowCloseEvent() : WindowEvent(Event::WindowClose) {}
    //TODO
};


#endif
