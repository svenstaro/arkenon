#include "window/GameWindow.hpp"

#include <iostream>

#include "render/Font.hpp"

GameWindow::GameWindow()
    : Window("Arkenon", glm::vec2(800, 600))
{}

void GameWindow::onEvent(const Event* event)
{
    if(event->type == Event::KeyPress) {
        KeyPressEvent* e = (KeyPressEvent*) event;
        if(e->key == GLFW_KEY_ESCAPE)
            close();
    }
}
