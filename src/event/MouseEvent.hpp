#ifndef _EVENT_MOUSEEVENT_HPP
#define _EVENT_MOUSEEVENT_HPP

#include "Event.hpp"

#include <glm/glm.hpp>

class MouseEvent : public Event {
public:
    MouseEvent(Type _type) : Event(_type) {}
    glm::vec2 position;
};

class MousePressEvent : public MouseEvent {
public:
    MousePressEvent() : MouseEvent(Event::MousePress) {}
    int button, mods;
};

class MouseReleaseEvent : public MouseEvent {
public:
    MouseReleaseEvent() : MouseEvent(Event::MouseRelease) {}
    int button, mods;
};

class MouseMoveEvent : public MouseEvent {
public:
    MouseMoveEvent() : MouseEvent(Event::MouseMove) {}
};

class MouseScrollEvent : public MouseEvent {
public:
    MouseScrollEvent() : MouseEvent(Event::MouseScroll) {}
    glm::vec2 delta;
};

class MouseEnterEvent : public MouseEvent {
public:
    MouseEnterEvent() : MouseEvent(Event::MouseEnter) {}
};

class MouseLeaveEvent : public MouseEvent {
public:
    MouseLeaveEvent() : MouseEvent(Event::MouseLeave) {}
};


#endif
