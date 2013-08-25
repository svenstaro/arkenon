#include "InputReceiver.hpp"

InputReceiver::~InputReceiver()
{}

void InputReceiver::addInputForwarding(InputReceiver* receiver)
{
    mForwards.push_back(receiver);
}

void InputReceiver::mouseButtonPressed(int button, int mods)
{
    onMouseButtonPressed(button, mods);
    for(auto forward : mForwards) forward->mouseButtonPressed(button, mods);
}

void InputReceiver::mouseButtonReleased(int button, int mods)
{
    onMouseButtonReleased(button, mods);
    for(auto forward : mForwards) forward->mouseButtonReleased(button, mods);
}

void InputReceiver::mouseMoved(double x, double y)
{
    onMouseMoved(x, y);
    for(auto forward : mForwards) forward->mouseMoved(x, y);
}

void InputReceiver::mouseScrolled(double dx, double dy)
{
    onMouseScrolled(dx, dy);
    for(auto forward : mForwards) forward->mouseScrolled(dx, dy);
}

void InputReceiver::mouseEnter()
{
    onMouseEnter();
    for(auto forward : mForwards) forward->mouseEnter();
}

void InputReceiver::mouseLeave()
{
    onMouseLeave();
    for(auto forward : mForwards) forward->mouseLeave();
}

void InputReceiver::keyPressed(int key, int scancode, int mods, bool repeated)
{
    onKeyPressed(key, scancode, mods, repeated);
    for(auto forward : mForwards) forward->keyPressed(key, scancode, mods, repeated);
}

void InputReceiver::keyReleased(int key, int scancode, int mods)
{
    onKeyReleased(key, scancode, mods);
    for(auto forward : mForwards) forward->keyReleased(key, scancode, mods);
}

void InputReceiver::characterTyped(unsigned int unicode)
{
    onCharacterTyped(unicode);
    for(auto forward : mForwards) forward->characterTyped(unicode);
}

void InputReceiver::onMouseButtonPressed(int button, int mods) {}
void InputReceiver::onMouseButtonReleased(int button, int mods) {}
void InputReceiver::onMouseMoved(double x, double y) {}
void InputReceiver::onMouseScrolled(double dx, double dy) {}
void InputReceiver::onMouseEnter() {}
void InputReceiver::onMouseLeave() {}
void InputReceiver::onKeyPressed(int key, int scancode, int mods, bool repeated) {}
void InputReceiver::onKeyReleased(int key, int scancode, int mods) {}
void InputReceiver::onCharacterTyped(unsigned int unicode) {}
