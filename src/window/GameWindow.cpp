#include "window/GameWindow.hpp"

#include <iostream>

GameWindow::GameWindow()
    : Window("Bridge Party")
{}

void GameWindow::onMouseButtonReleased(int button, int mods)
{
    std::cout << "Mouse button " << button << " released." << std::endl;
}

void GameWindow::onCharacterTyped(unsigned int unicode)
{
    std::cout << "Character typed: " << unicode << std::endl;
}

void GameWindow::onKeyPressed(int key, int scancode, int mods, bool repeated)
{
    if(key == GLFW_KEY_ESCAPE)
    {
        close();
    }
}
