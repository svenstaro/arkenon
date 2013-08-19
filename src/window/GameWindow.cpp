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
