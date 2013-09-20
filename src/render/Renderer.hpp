#ifndef _RENDER_RENDERER_HPP
#define _RENDER_RENDERER_HPP

#include "render/Light.hpp"
#include "scene/Node.hpp"
#include "scene/Camera.hpp"

#include <vector>

class Renderer {
public:
    Renderer();
    Renderer(glm::vec2 size);

    virtual void prepare();
    void prepareScene(Node* node, Node::RenderTechnique render_technique);
    void registerRenderNode(Node* node);
    void registerLight(Light* light);
    void setSize(glm::vec2 size);
    void setCamera(std::shared_ptr<Camera> camera);
    virtual void render() = 0;
    virtual void cleanup();

protected:
    virtual void onResize(glm::vec2 size);

    std::vector<Light*> mLights;
    std::vector<Node*> mRenderNodes;
    std::shared_ptr<Camera> mCamera;
    glm::vec2 mSize;

};

#endif
