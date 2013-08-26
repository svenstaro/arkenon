#ifndef _EVENT_KEYBOARDEVENT_HPP
#define _EVENT_KEYBOARDEVENT_HPP

#include "Event.hpp"

#include <glm/glm.hpp>

class KeyboardEvent : public Event {
public:
    KeyboardEvent(Type _type) : Event(_type) {}
};

class KeyPressEvent : public KeyboardEvent {
public:
    KeyPressEvent() : KeyboardEvent(Event::KeyPress) {}
    int key, scancode, mods;
    bool repeated;
};

class KeyReleaseEvent : public KeyboardEvent {
public:
    KeyReleaseEvent() : KeyboardEvent(Event::KeyRelease) {}
    int key, scancode, mods;
};

class CharacterEvent : public KeyboardEvent {
public:
    CharacterEvent() : KeyboardEvent(Event::Character) {}
    unsigned int unicode;
};

#endif
