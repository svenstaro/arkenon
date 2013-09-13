#ifndef _SCENE_DEBUGSCENE_HPP
#define _SCENE_DEBUGSCENE_HPP

#include <memory>

#include "scene/Node.hpp"
#include "window/Window.hpp"
#include "render/deferred/DeferredRenderer.hpp"
#include "render/ForwardRenderer.hpp"
#include "render/Material.hpp"
#include "scene/Mesh.hpp"
#include "render/Shape2D.hpp"
#include "scene/FreeCamera.hpp"

#include "audio/AudioDevice.hpp"

class DebugScene : public Node {
public:
    DebugScene(Window& window);

    void initialize();

    void onUpdate(double dt);
    void onEvent(const Event *event);
    void render();

private:
    Window& mWindow;
    AudioDevice mAudioDevice;

    std::shared_ptr<Camera> mCamera;
    std::vector<std::shared_ptr<Light>> mLights;

    void _addDebugMesh(const std::string& name, const glm::vec3 pos, const glm::vec4& color, std::shared_ptr<Material> material = nullptr);

    DeferredRenderer mDeferredRenderer;
    ForwardRenderer mForwardRenderer;

    bool mPaused;
    double mTime;
};

#endif
