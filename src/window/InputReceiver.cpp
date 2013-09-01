#include "InputReceiver.hpp"

InputReceiver::~InputReceiver()
{}

void InputReceiver::addInputForwarding(InputReceiver* receiver)
{
    mForwards.push_back(receiver);
}

void InputReceiver::handleUpdate(double dt)
{
    onUpdate(dt);
    for(auto forward : mForwards) forward->handleUpdate(dt);
}

void InputReceiver::handleEvent(const Event* event)
{
    onEvent(event);
    for(auto forward : mForwards) forward->handleEvent(event);
}

void InputReceiver::onUpdate(double dt) {}
void InputReceiver::onEvent(const Event* event) {}
