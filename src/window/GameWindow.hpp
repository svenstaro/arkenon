#ifndef _WINDOW_GAMEWINDOW_HPP
#define _WINDOW_GAMEWINDOW_HPP

#include "window/Window.hpp"

class GameWindow : public Window {
public:
    GameWindow();

    void onEvent(const Event *event);
};

#endif
