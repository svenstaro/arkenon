#ifndef _WINDOW_GAMEWINDOW_HPP
#define _WINDOW_GAMEWINDOW_HPP

#include "window/Window.hpp"

class GameWindow : public Window {
public:
    GameWindow();

    void onMouseButtonReleased(int button, int mods);
    void onCharacterTyped(unsigned int unicode);
    void onKeyPressed(int key, int scancode, int mods, bool repeated);
};

#endif
