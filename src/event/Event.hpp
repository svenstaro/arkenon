#ifndef _EVENT_EVENT_HPP
#define _EVENT_EVENT_HPP

#include <string>

class Window;

class Event {
public:
    enum Type {
        MousePress,
        MouseRelease,
        MouseMove,
        MouseScroll,
        MouseEnter,
        MouseLeave,
        KeyPress,
        KeyRelease,
        Character,
        WindowResize,
        WindowClose,
        WindowMove,
        WindowDefocus,
        WindowFocus
    };

    Event(Type _type);
    virtual ~Event() = 0;

    Type type;

    std::string getTypeString() const;

    Window* window;
};

#endif
