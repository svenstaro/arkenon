#include <iostream>
#include <memory>
#include <algorithm> 
#include <sstream>
#include <math.h>

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
#include "render/deferred/DeferredRenderer.hpp"
#include "render/FlatRenderer.hpp"
#include "render/Framebuffer.hpp"
#include "render/Font.hpp"
#include "render/Shape3D.hpp"
#include "render/Shape2D.hpp"
#include "gui/Label.hpp"
#include "scene/Mesh.hpp"
#include "scene/Camera.hpp"
#include "gui/Frame.hpp"
#include "gui/Button.hpp"

int main()
{
    Font::defaultFont = std::make_shared<Font>("data/fonts/OpenSans-Regular.ttf");
    GameWindow window;
    FlatRenderer guiRenderer;

    std::shared_ptr<Material> gui = std::make_shared<Material>();
    gui->setDiffuseTexture(std::make_shared<Texture>("data/gui/button.png"));

    std::shared_ptr<Button> button_left = std::make_shared<Button>("<");
    button_left->setMaterial(gui);
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
    button_right->setMaterial(gui);
    button_right->setSplit9Factor(glm::vec2(152/216.f, 8/56.f));
    button_right->setSubrect(Button::Normal, Rect(0,        0, 216/256.f, 56/256.f));
    button_right->setSubrect(Button::Hover,  Rect(0, 56/256.f, 216/256.f, 56/256.f));
    button_right->setSubrect(Button::Focus,  Rect(0, 56/256.f, 216/256.f, 56/256.f));
    button_right->setSubrect(Button::Active, Rect(0,112/256.f, 216/256.f, 56/256.f));
    button_right->setSize(glm::vec2(216, 56));
    button_right->position = glm::vec3(window.getSize().x / 2 + 10, 20, 0);
    button_right->setColor(glm::vec4(1, 1, 1, 1));
    button_right->setFontSize(12);

    std::shared_ptr<Label> fps_label = std::make_shared<Label>("FPS: 0");
    fps_label->setFontSize(20);
    fps_label->setAlign(Text::Start, Text::Start);
    fps_label->position = glm::vec3(10, 10, 0);

    std::shared_ptr<Camera> guiCamera = std::make_shared<Camera>("gui-camera", Camera::Screen, window.getSize(), 1.f);
    window.addInputForwarding(button_left.get());
    window.addInputForwarding(button_right.get());

    while(window.isOpen()) {
        window.update();
        window.bind();
        window.clear();
        window.render();

        // render a little bit of GUI
        guiCamera->setViewportSize(window.getSize());
        guiCamera->position = glm::vec3(window.getSize().x * 0.5f, window.getSize().y * 0.5f, 2.f);
        std::stringstream fps_string("");
        fps_string << "FPS: " << round(window.getFPS());
        fps_label->setText(fps_string.str());

        guiRenderer.prepare();
        guiRenderer.registerRenderable(button_right);
        guiRenderer.registerRenderable(button_left);
        guiRenderer.registerRenderable(fps_label);
        guiRenderer.setCamera(guiCamera);
        guiRenderer.render();
        guiRenderer.cleanup();

        window.display();
    }

    return 0;
}
