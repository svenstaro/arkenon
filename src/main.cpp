#include <iostream>

#include "window/GameWindow.hpp"
#include "render/Shader.hpp"
#include "render/ShaderProgram.hpp"

int main()
{
    GameWindow window;
    window.setSize(1024, 600);

    Shader simple_vertex(Shader::Vertex, "data/shader/simple.vertex.glsl");
    Shader simple_fragment(Shader::Fragment, "data/shader/simple.fragment.glsl");
    ShaderProgram simple;
    simple.attach(simple_vertex);
    simple.attach(simple_fragment);
    simple.link();

    while(window.isOpen()) {
        window.update();
        window.display();
    }

    return 0;
}
