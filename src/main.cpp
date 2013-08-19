#include <iostream>

#include "window/GameWindow.hpp"

int main()
{
    GameWindow window;
    window.setSize(1024, 600);

    while(window.isOpen()) {
        window.update();
        window.display();
    }

    return 0;
}
