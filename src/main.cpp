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
#include "render/ForwardRenderer.hpp"
#include "render/FlatRenderer.hpp"
#include "render/Framebuffer.hpp"
#include "render/Font.hpp"
#include "gui/Label.hpp"
#include "scene/Mesh.hpp"
#include "scene/Camera.hpp"
#include "gui/Frame.hpp"
#include "gui/Button.hpp"

// TESTING INCLUDES
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
    Font::defaultFont = std::make_shared<Font>("data/fonts/OpenSans-Regular.ttf");

    GameWindow window;
    window.setBackgroundColor(glm::vec4(0.2, 0.3, 0.5, 1.f));
    window.setBackgroundColor(glm::vec4(0.02, 0.02, 0.02, 1.f));
    //window.setSize(1024, 600);

    ForwardRenderer renderer;
    FlatRenderer guiRenderer;

    Node root("root");
    std::shared_ptr<Mesh> mesh(new Mesh("mesh"));
    root.addChild(mesh);

    window.addInputForwarding(&root);

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("data/models/fighter.dae", aiProcessPreset_TargetRealtime_Fast);
    mesh->load(scene->mMeshes[0]);
    mesh->commit();

    std::shared_ptr<Texture> texture(new Texture());
    texture->load("data/textures/fighter.png");
    texture->setSmooth(false);
    mesh->setDiffuseTexture(texture);

    std::shared_ptr<Camera> camera(new Camera("camera", Camera::Perspective, window.getSize(), 60.f));
    root.addChild(camera);
    camera->position = glm::vec3(0, 3, 6);
    camera->rotation = glm::quat(glm::vec3(-0.5, 0, 0));

    std::shared_ptr<Texture> gui(new Texture());
    gui->load("data/gui/button.png");

    std::shared_ptr<Button> button_left = std::make_shared<Button>("<");
    button_left->setTexture(gui);
    button_left->setSplit9Factor(glm::vec2(152/216.f, 8/56.f));
    button_left->setSubrect(Button::Normal, Rect(0,        0, 216/256.f, 56/256.f));
    button_left->setSubrect(Button::Hover,  Rect(0, 56/256.f, 216/256.f, 56/256.f));
    button_left->setSubrect(Button::Focus,  Rect(0, 56/256.f, 216/256.f, 56/256.f));
    button_left->setSubrect(Button::Active, Rect(0,112/256.f, 216/256.f, 56/256.f));
    button_left->setSize(glm::vec2(216, 56));
    button_left->position = glm::vec3(window.getSize().x / 2 - 216 - 10, 20, 0);
    button_left->setColor(glm::vec4(1, 1, 1, 1));
    button_left->setFontSize(12);

    std::shared_ptr<Button> button_right = std::make_shared<Button>(">");
    button_right->setTexture(gui);
    button_right->setSplit9Factor(glm::vec2(152/216.f, 8/56.f));
    button_right->setSubrect(Button::Normal, Rect(0,        0, 216/256.f, 56/256.f));
    button_right->setSubrect(Button::Hover,  Rect(0, 56/256.f, 216/256.f, 56/256.f));
    button_right->setSubrect(Button::Focus,  Rect(0, 56/256.f, 216/256.f, 56/256.f));
    button_right->setSubrect(Button::Active, Rect(0,112/256.f, 216/256.f, 56/256.f));
    button_right->setSize(glm::vec2(216, 56));
    button_right->position = glm::vec3(window.getSize().x / 2 + 10, 20, 0);
    button_right->setColor(glm::vec4(1, 1, 1, 1));
    button_right->setFontSize(12);

    std::shared_ptr<Camera> guiCamera(new Camera("gui-camera", Camera::Screen, window.getSize(), 1.f));

    window.addInputForwarding(button_left.get());
    window.addInputForwarding(button_right.get());

    double time = 0, angle = M_PI/2, angleSpeed = 0;
    while(window.isOpen()) {
        window.update();
        window.setActive();

        camera->setViewportSize(window.getSize());
        guiCamera->setViewportSize(window.getSize());
        guiCamera->position = glm::vec3(window.getSize().x * 0.5f, window.getSize().y * 0.5f, 2.f);

        time += window.getFrameDuration();
        if(button_left->getState() == Button::Active)
            angleSpeed -= window.getFrameDuration() * 3;
        else if(button_right->getState() == Button::Active)
            angleSpeed += window.getFrameDuration() * 3;
        else
            angleSpeed *= (1 - window.getFrameDuration());
        angle += angleSpeed * window.getFrameDuration();
        mesh->rotation = glm::quat(glm::vec3(-M_PI/2, angle, 0));
        mesh->position = glm::vec3(-cos(angle), 0, sin(angle)) * 3.f;

        window.clear();

        renderer.prepare();
        renderer.registerRenderable(mesh);
        renderer.setCamera(camera);
        renderer.render();
        renderer.cleanup();

        guiRenderer.prepare();
        guiRenderer.registerRenderable(button_right);
        guiRenderer.registerRenderable(button_left);
        guiRenderer.setCamera(guiCamera);
        guiRenderer.render();
        guiRenderer.cleanup();



        window.display();
    }

    return 0;
}
