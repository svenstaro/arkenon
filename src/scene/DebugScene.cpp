#include "DebugScene.hpp"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <AL/alure.h>

#include <sstream>


#include "audio/StreamedSound.hpp"
#include "audio/Stream.hpp"
#include "audio/Buffer.hpp"
#include "audio/Playlist.hpp"
#include "audio/Sound.hpp"
#include "audio/Listener.hpp"

#include "util/check.hpp"

DebugScene::DebugScene(Window& window)
    : Node("debug-scene"),
      mWindow(window),
      mSkyRenderer(window.getSize()),
      mDeferredRenderer(window.getSize()),
      mPaused(false),
      mTime(0)
{
}

void DebugScene::initialize()
{

    // create camera mover
    std::shared_ptr<FreeCamera> freeCamera = std::make_shared<FreeCamera>("free-camera", mWindow);
    freeCamera->position = glm::vec3(-12, 5, -1);
    freeCamera->rotation = glm::quat(glm::vec3(-0.3, -M_PI/2, 0));
    addChild(freeCamera);

    // create camera
    mCamera = std::make_shared<Camera>("camera", Camera::Perspective, mWindow.getSize(), 60.f);
    freeCamera->addChild(mCamera);

    std::shared_ptr<Listener> listener = std::make_shared<Listener>("listener");
    freeCamera->addChild(listener);

    //Playlist music
    /*
    std::vector<std::string> playlist;
    playlist.push_back("data/sounds/dark_intro.ogg");
    playlist.push_back("data/sounds/IswearIsawit.ogg");
    playlist.push_back("data/sounds/spacecrusher.ogg");

    std::shared_ptr<Playlist> backgroundMusic = std::make_shared<Playlist>("music_playlist", playlist);
    backgroundMusic->setRelativeToListener(true);
    backgroundMusic->setLoop(true);
    backgroundMusic->setVolume(100.0);
    backgroundMusic->play();
    addChild(backgroundMusic);
    */

    mSpacecraft = std::make_shared<Spacecraft>("spacecraft");
    mSpacecraft->initialize();
    addChild(mSpacecraft);

    // create materials
    std::shared_ptr<Material> wallMaterial = std::make_shared<Material>();
    wallMaterial->setDiffuseTexture(std::make_shared<Texture>("data/textures/brick-round/brick-round-diffuse.jpg"));
    wallMaterial->setNormalTexture(std::make_shared<Texture>("data/textures/brick-round/brick-round-normal.jpg"));
    wallMaterial->setSpecularTexture(std::make_shared<Texture>("data/textures/brick-round/brick-round-specular.jpg"));

    std::shared_ptr<Material> groundMaterial = std::make_shared<Material>();
    groundMaterial->setDiffuseTexture(std::make_shared<Texture>("data/textures/pattern_262/diffuse.tga"));
    groundMaterial->setNormalTexture(std::make_shared<Texture>("data/textures/pattern_262/normal.tga"));

    // add debug meshes
    _addDebugMesh("wall", glm::vec3(-5, 1.68945, 2), glm::vec4(1, 1, 1, 1), wallMaterial);
    _addDebugMesh("cube", glm::vec3(0, 0, 0), glm::vec4(1, 0, 0, 1));
    _addDebugMesh("sphere", glm::vec3(-5, 1, -5), glm::vec4(1, 1, 0, 1));
    _addDebugMesh("columns", glm::vec3(5.5, 0, -2), glm::vec4(.5, 0, .7, 1));
    _addDebugMesh("debug", glm::vec3(4.5, 0, 3), glm::vec4(0.3, 0.5, 1, 1));

    // add ground
    std::shared_ptr<Shape2D> ground = std::make_shared<Shape2D>("ground");
    ground->setMaterial(groundMaterial);
    ground->makeRectangle(glm::vec2(100, 100), Rect(0, 0, 10, 10));
    ground->position = glm::vec3(-50, 0, -50);
    ground->rotation = glm::quat(glm::vec3(M_PI/2, 0, 0));
    addChild(ground);

    // add some lights
    for(unsigned int i = 1; i < 3; ++i)
    {
        std::shared_ptr<Light> light(new Light("light-" + std::to_string(i)));
        light->setColor(glm::vec4(1, 1, 1, 1));
        light->setRadius(i==0 ? 30 : 10.0f);
        light->position = glm::vec3(0, 20, 0);
        addChild(light);
        mLights.push_back(light);
    }

    //getChild("light-1")->addChild(soundEmitter);

    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("data/models/fighter.dae", aiProcessPreset_TargetRealtime_Fast);

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>("fighter");
    mesh->load(scene->mMeshes[0]);
    mesh->commit();
    mesh->rotation = glm::quat(glm::vec3(-M_PI/2, 0, 0));
    mesh->position = glm::vec3(0, 0, 10);
    std::shared_ptr<Material> material = std::make_shared<Material>();
    material->setDiffuseTexture(std::make_shared<Texture>("data/textures/fighter.png"));
    material->setSpecularShininess(10);

    material->setDiffuseColor(glm::vec4(0.5, 0.5, 0.5, 1.0));
    mesh->setMaterial(material);
    addChild(mesh);
}

void DebugScene::onUpdate(double dt)
{
    if(!mPaused) mTime += dt;

    for(unsigned int i = 0; i < mLights.size(); ++i)
    {
        std::shared_ptr<Light> light = mLights[i];
        light->position.x = sin(M_PI * i + mTime) * 10;
        light->position.z = cos(M_PI * i + mTime) * 10;
        light->position.y = 3;
    }
}

void DebugScene::onEvent(const Event* event)
{
    if(event->type == Event::KeyPress) {
        KeyPressEvent* e = (KeyPressEvent*) event;
        if(e->key == GLFW_KEY_SPACE) {
            mPaused = !mPaused;
        }
    }

    if(event->type == Event::WindowResize) {
        WindowResizeEvent* e = (WindowResizeEvent*) event;
        mDeferredRenderer.setSize(glm::vec2(e->width, e->height));
        mCamera->setViewportSize(glm::vec2(e->width, e->height));

        //std::cout << e->width << ", " << e->height << std::endl;
    }
}

void DebugScene::render()
{
    // update size
    mCamera->setViewportSize(mWindow.getSize());
    mDeferredRenderer.setSize(mWindow.getSize());
    mSkyRenderer.setSize(mWindow.getSize());

    // render background
    mSkyRenderer.prepare();
    mSkyRenderer.setCamera(mCamera);
    //mSkyRenderer.render();
    mSkyRenderer.cleanup();

    // prepare renderer
    mDeferredRenderer.prepare();
    mDeferredRenderer.prepareScene(this, Node::Deferred);
    mDeferredRenderer.setCamera(mCamera);

    for(unsigned int i = 0; i < mLights.size(); ++i)
        mDeferredRenderer.registerLight(mLights[i].get());

    // render and cleanup
    mDeferredRenderer.render();
    mDeferredRenderer.cleanup();
}

void DebugScene::_addDebugMesh(const std::string& name, const glm::vec3 pos, const glm::vec4& color, std::shared_ptr<Material> material)
{
    Assimp::Importer importer;
    const aiScene *scene = importer.ReadFile("data/models/debug/" + name + ".dae", aiProcessPreset_TargetRealtime_Fast);

    std::shared_ptr<Mesh> mesh = std::make_shared<Mesh>(name);
    mesh->load(scene->mMeshes[0]);
    mesh->commit();
    mesh->rotation = glm::quat(glm::vec3(-M_PI/2, 0, 0));
    mesh->position = pos;
    if(!material) {
        material = std::make_shared<Material>();
    }
    material->setDiffuseColor(color);
    mesh->setMaterial(material);
    addChild(mesh);
}
