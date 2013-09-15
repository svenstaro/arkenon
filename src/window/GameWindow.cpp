#include "window/GameWindow.hpp"

#include <iostream>

#include "render/Font.hpp"

GameWindow::GameWindow()
    : Window("Arkenon", glm::vec2(800, 600)),
      mDebugScene(*this)
{
    setCursorMode(Window::Captured);
    mDebugScene.initialize();
    addInputForwarding(&mDebugScene);
}

void GameWindow::render()
{
    mDebugScene.render();
}

void GameWindow::onEvent(const Event* event)
{
    if(event->type == Event::KeyPress) {
        KeyPressEvent* e = (KeyPressEvent*) event;
        if(e->key == GLFW_KEY_ESCAPE)
            close();
    } else if(event->type == Event::MousePress) {
        if(((MousePressEvent*)event)->button != GLFW_MOUSE_BUTTON_RIGHT) return;
        if(getCursorMode() == Window::Normal)
            setCursorMode(Window::Captured);
        else
            setCursorMode(Window::Normal);
    }
}
