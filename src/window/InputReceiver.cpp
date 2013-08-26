#include "InputReceiver.hpp"

InputReceiver::~InputReceiver()
{}

void InputReceiver::addInputForwarding(InputReceiver* receiver)
{
    mForwards.push_back(receiver);
}

void InputReceiver::handleEvent(const Event* event)
{
    onEvent(event);
    for(auto forward : mForwards) forward->handleEvent(event);
}

void InputReceiver::onEvent(const Event* event) {}
