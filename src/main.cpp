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

// TESTING INCLUDES
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

int main()
{
    Font::defaultFont = std::make_shared<Font>("data/fonts/OpenSans-Regular.ttf");

    GameWindow window;
    window.setBackgroundColor(glm::vec4(0.2, 0.3, 0.5, 1.f));
    //window.setBackgroundColor(glm::vec4(0.02, 0.02, 0.02, 1.f));
    window.setBackgroundColor(glm::vec4(0, 0, 0, 1));
    //window.setSize(1024, 600);

    DeferredRenderer deferredRenderer(window.getSize());
    ForwardRenderer forwardRenderer;
    FlatRenderer guiRenderer;

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("data/models/fighter.dae", aiProcessPreset_TargetRealtime_Fast);

    std::shared_ptr<Texture> texture(new Texture());
    texture->load("data/textures/fighter.png");
    texture->setSmooth(false);

    Node ship("ship");
    ship.position.y = 2;
    window.addInputForwarding(&ship);

    std::shared_ptr<Mesh> mesh(new Mesh("mesh"));
    mesh->load(scene->mMeshes[0]);
    mesh->commit();
    mesh->rotation = glm::quat(glm::vec3(-M_PI/2, 0, 0));
    mesh->setDiffuseTexture(texture);
    ship.addChild(mesh);

    std::shared_ptr<Camera> camera(new Camera("camera", Camera::Perspective, window.getSize(), 60.f));
    ship.addChild(camera);
    camera->position = glm::vec3(0, 5, -10);
    camera->rotation = glm::quat(glm::vec3(-0.25, M_PI, 0));

    std::shared_ptr<Light> light(new Light("ship_light"));
    light->setColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
    light->setRadius(12.0f);
    ship.addChild(light);

    std::shared_ptr<Light> staticLight(new Light("static_light"));
    staticLight->setColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    staticLight->setRadius(12.0f);
    staticLight->position.y = 2;

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

    std::shared_ptr<Texture> groundTexture = std::make_shared<Texture>();
    groundTexture->load("data/textures/pattern_262/diffuse.tga");

    std::shared_ptr<Shape2D> ground = std::make_shared<Shape2D>("ground");
    ground->setTexture(groundTexture);
    ground->makeRectangle(glm::vec2(100, 100), Rect(0, 0, 10, 10));
    ground->position = glm::vec3(-50, 0, -50);
    ground->rotation = glm::quat(glm::vec3(M_PI/2, 0, 0));

    std::shared_ptr<Texture> gridTexture = std::make_shared<Texture>();
    gridTexture->setMipmap(true);
    gridTexture->load("data/gfx/grid.png");

    std::shared_ptr<Shape2D> grid = std::make_shared<Shape2D>("grid");
    grid->setTexture(gridTexture);
    grid->makeRectangle(glm::vec2(100, 100), Rect(0, 0, 100, 100));
    grid->position = glm::vec3(-50, 0.1, -50);
    grid->rotation = glm::quat(glm::vec3(M_PI/2, 0, 0));

    float speed = 0;
    float rotSpeed = 0;
    float angle = 0;

    while(window.isOpen()) {
        window.update();
        window.bind();

        deferredRenderer.setSize(window.getSize());

        camera->setViewportSize(window.getSize());
        guiCamera->setViewportSize(window.getSize());
        guiCamera->position = glm::vec3(window.getSize().x * 0.5f, window.getSize().y * 0.5f, 2.f);

        float dt = window.getFrameDuration();

        if(window.isKeyDown(GLFW_KEY_UP))           speed += dt * 6;
        else if(window.isKeyDown(GLFW_KEY_DOWN))    speed -= dt * 6;
        else                                        speed *= (1 - dt);

        if(window.isKeyDown(GLFW_KEY_RIGHT))        rotSpeed -= dt * 5;
        else if(window.isKeyDown(GLFW_KEY_LEFT))    rotSpeed += dt * 5;
        else                                        rotSpeed *= (1 - dt);

        if(speed > 10) speed = 10;
        if(speed < -10) speed = -10;

        if(rotSpeed > 3) rotSpeed = 3;
        if(rotSpeed < -3) rotSpeed = -3;

        angle += rotSpeed * dt;

        ship.rotation = glm::quat(glm::vec3(0, angle, 0)) * glm::quat(glm::vec3(0, 0, 1 - pow(0.8, -rotSpeed)));
        ship.position += glm::vec3(sin(angle), 0, cos(angle)) * speed * dt;

        window.clear();

        deferredRenderer.prepare();

        //Objects
        deferredRenderer.registerRenderable(mesh);
        deferredRenderer.registerRenderable(ground);

        //Lights
        deferredRenderer.registerLight(light);
        deferredRenderer.registerLight(staticLight);

        //Camera
        deferredRenderer.setCamera(camera);

        deferredRenderer.render();
        deferredRenderer.cleanup();

        forwardRenderer.prepare();
        forwardRenderer.registerRenderable(grid);
        forwardRenderer.setCamera(camera);
        forwardRenderer.render();
        forwardRenderer.cleanup();

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
