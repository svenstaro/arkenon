#include <iostream>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include "window/GameWindow.hpp"
#include "render/Shader.hpp"
#include "render/ShaderProgram.hpp"
#include "render/VertexBuffer.hpp"
#include "scene/Mesh.hpp"
#include "scene/Camera.hpp"

int main()
{
    GameWindow window;
    //window.setSize(1024, 600);

    Shader simple_vertex(Shader::Vertex, "data/shader/simple.vertex.glsl");
    Shader simple_fragment(Shader::Fragment, "data/shader/simple.fragment.glsl");
    ShaderProgram simple;
    simple.attach(simple_vertex);
    simple.attach(simple_fragment);
    simple.link();

    Node root("root");
    Node* child1 = root.addChild(new Node("child1"));
    Node* child2 = root.addChild(new Node("child2"));
    Node* child21 = child2->addChild(new Node("child21"));
    Node* child22 = child2->addChild(new Node("child22"));

    Mesh* mesh = (Mesh*) root.addChild(new Mesh("mesh", &simple));
    mesh->addTriangle(Vertex(0.f, 1.f, 0.f, 0, 0, 1, 0, 0, 1),
                     Vertex(-1.f, -1.f, 0.f, 0, 0, 1, 0, 0, 1),
                     Vertex(1.f, -1.f, 0.f, 0, 0, 1, 0, 0, 1));
    mesh->addTriangle(Vertex(0.f, -1.f, 0.f, 0, 0, 0, 0, 1, 1),
                     Vertex(0.f, 1.f, -1.f, 0, 0, 0, 0, 1, 1),
                     Vertex(0.f, 1.f, 1.f, 0, 0, 0, 1, 0, 1));
    mesh->commit();

    glm::vec3 xAxis(1, 0, 0);
    glm::vec3 yAxis(0, 1, 0);

    Camera* camera = (Camera*) root.addChild(new Camera("camera", 60, window.getAspectRatio(), 0.1f, 100.f));
    camera->position = glm::vec3(0, 0, 3); // camera looks at -z
    //camera->rotation = glm::quat(glm::vec3(-0.1 * M_PI, 0, 0));

    glm::mat4 Projection = glm::perspective(45.0f, window.getAspectRatio(), 0.1f, 100.0f);
    glm::mat4 View       = glm::lookAt(glm::vec3(0,3,3), glm::vec3(0,0,0), yAxis);

    double time = 0;
    while(window.isOpen()) {
        window.update();
        window.clear();

        time = time + window.getFrameDuration();
        mesh->rotation = glm::quat(glm::vec3(0, window.getFrameDuration(), 0)) * mesh->rotation;

        ((Mesh*) root.getChild("mesh"))->render((Camera*) root.getChild("camera"));

        window.display();
    }

    return 0;
}
