#include <iostream>

#include "window/GameWindow.hpp"
#include "render/Shader.hpp"
#include "render/ShaderProgram.hpp"
#include "render/VertexBuffer.hpp"

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

    VertexBuffer vb;
    vb.addVertex(0, 1, 0);
    vb.addVertex(-1, -1, 0);
    vb.addVertex(1, -1, 0);
    vb.commit();

    while(window.isOpen()) {
        window.update();
        window.clear();
        simple.use();
        vb.draw();
        window.display();
    }

    return 0;
}
