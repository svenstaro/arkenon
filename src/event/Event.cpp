#include "Event.hpp"

Event::Event(Event::Type _type)
    : type(_type)
{}

Event::~Event()
{}

std::string Event::getTypeString() const
{
    switch(type) {
        case MousePress:    return "MousePress";
        case MouseRelease:  return "MouseRelease";
        case MouseMove:     return "MouseMove";
        case MouseScroll:   return "MouseScroll";
        case MouseEnter:    return "MouseEnter";
        case MouseLeave:    return "MouseLeave";
        case KeyPress:      return "KeyPress";
        case KeyRelease:    return "KeyRelease";
        case Character:     return "Character";
        case WindowResize:  return "WindowResize";
        case WindowClose:   return "WindowClose";
        case WindowMove:    return "WindowMove";
        case WindowDefocus: return "WindowDefocus";
        case WindowFocus:   return "WindowFocus";
        default:            return "?UnknownEvent?";
    }
}
