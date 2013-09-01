#ifndef _WINDOW_GAMEWINDOW_HPP
#define _WINDOW_GAMEWINDOW_HPP

#include "window/Window.hpp"
#include "scene/DebugScene.hpp"

class GameWindow : public Window {
public:
    GameWindow();

    void render();
    void onEvent(const Event *event);

private:
    DebugScene mDebugScene;
};

#endif
