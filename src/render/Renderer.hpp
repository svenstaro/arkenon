#ifndef _RENDER_RENDERER_HPP
#define _RENDER_RENDERER_HPP

#include "render/Renderable.hpp"
#include "render/Light.hpp"
#include "scene/Node.hpp"
#include "scene/Camera.hpp"

#include <vector>

class Renderer {
public:
    Renderer();
    Renderer(glm::vec2 size);

    virtual void prepare();
    void prepareScene(Node* node);
    void registerRenderable(std::shared_ptr<Node> renderable);
    void registerRenderable(Renderable* renderable);
    void registerLight(std::shared_ptr<Node> light);
    void registerLight(Light* light);
    void setSize(glm::vec2 size);
    void setCamera(std::shared_ptr<Camera> camera);
    virtual void render() = 0;
    virtual void cleanup();

protected:
    virtual void onResize(glm::vec2 size);

    std::vector<Light*> mLights;
    std::vector<Renderable*> mRenderables;
    std::shared_ptr<Camera> mCamera;
    glm::vec2 mSize;

};

#endif
