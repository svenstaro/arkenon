#ifndef _WINDOW_INPUTRECEIVER_HPP
#define _WINDOW_INPUTRECEIVER_HPP

#include <vector>
#include <memory>

#include "event/Event.hpp"
#include "event/MouseEvent.hpp"
#include "event/KeyboardEvent.hpp"
#include "event/WindowEvent.hpp"

class InputReceiver {
public:
    virtual ~InputReceiver() = 0;

    void addInputForwarding(InputReceiver* receiver);
    void handleEvent(const Event* event);
    virtual void onEvent(const Event* event);

protected:
    std::vector<InputReceiver*> mForwards;

};

#endif
