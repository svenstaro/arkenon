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
#include "gui/WidgetSkin.hpp"
#include "gui/Input.hpp"

int main()
{
    Font::defaultFont = std::make_shared<Font>("data/fonts/OpenSans-Regular.ttf");
    GameWindow window;
    FlatRenderer guiRenderer;

    std::shared_ptr<Texture> gui = std::make_shared<Texture>("data/gfx/gui.png");

    float p = 1/256.f; // pixel size
    Rect middle(0.25, 0.25, 0.5, 0.5);

    std::shared_ptr<WidgetSkin> buttonSkin = std::make_shared<WidgetSkin>();
    buttonSkin->setTextColor(glm::vec4(1, 1, 1, 1));
    buttonSkin->setTextureSubrect(WidgetSkin::Normal,   TextureSubrect(gui, Rect(  0*p,   0*p,  16*p,  16*p), middle));
    buttonSkin->setTextureSubrect(WidgetSkin::Focus,    TextureSubrect(gui, Rect( 16*p,   0*p,  16*p,  16*p), middle));
    buttonSkin->setTextureSubrect(WidgetSkin::Active,   TextureSubrect(gui, Rect( 32*p,   0*p,  16*p,  16*p), middle));
    buttonSkin->setTextureSubrect(WidgetSkin::Disabled, TextureSubrect(gui, Rect( 48*p,   0*p,  16*p,  16*p), middle));

    std::shared_ptr<WidgetSkin> inputSkin = std::make_shared<WidgetSkin>();
    inputSkin->setTextColor(glm::vec4(1, 1, 1, 1));
    inputSkin->setTextureSubrect(WidgetSkin::Normal,   TextureSubrect(gui, Rect(  0*p,   0*p,  16*p,  16*p), middle));
    inputSkin->setTextureSubrect(WidgetSkin::Focus,    TextureSubrect(gui, Rect( 16*p,   0*p,  16*p,  16*p), middle));
    inputSkin->setTextureSubrect(WidgetSkin::Active,   TextureSubrect(gui, Rect( 16*p,   0*p,  16*p,  16*p), middle));
    inputSkin->setTextureSubrect(WidgetSkin::Disabled, TextureSubrect(gui, Rect( 48*p,   0*p,  16*p,  16*p), middle));

    std::shared_ptr<Frame> frame = std::make_shared<Frame>("frame");
    window.addInputForwarding(frame.get());

    std::shared_ptr<Button> button_left = std::make_shared<Button>("button_left", "<");
    button_left->setSkin(buttonSkin);
    button_left->setSize(glm::vec2(100, 30));
    button_left->position = glm::vec3(window.getSize().x / 2 - 100 - 10, 20, 0);
    frame->addChild(button_left);

    std::shared_ptr<Button> button_right = std::make_shared<Button>("button_right", ">");
    button_right->setSkin(buttonSkin);
    button_right->setSize(glm::vec2(100, 30));
    button_right->position = glm::vec3(window.getSize().x / 2 + 10, 20, 0);
    frame->addChild(button_right);

    std::shared_ptr<Input> input = std::make_shared<Input>("input", "Enter something");
    input->setSkin(inputSkin);
    input->setSize(glm::vec2(200, 20));
    input->position = glm::vec3(10, 50, 0);
    frame->addChild(input);

    std::shared_ptr<Label> fps_label = std::make_shared<Label>("fps_label", "FPS: 0");
    fps_label->setFontSize(20);
    fps_label->setAlign(Text::Start, Text::Start);
    fps_label->position = glm::vec3(10, 10, 0);
    frame->addChild(fps_label);

    std::shared_ptr<Camera> guiCamera = std::make_shared<Camera>("gui-camera", Camera::Screen, window.getSize(), 1.f);

    while(true) {
        window.update();
        if(!window.isOpen()) break;

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
        guiRenderer.prepareScene(frame.get(), Node::GUI);
        guiRenderer.setCamera(guiCamera);
        guiRenderer.render();
        guiRenderer.cleanup();

        window.display();
    }

    return 0;
}
