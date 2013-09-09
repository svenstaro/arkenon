#ifndef _RENDER_RENDERER_HPP
#define _RENDER_RENDERER_HPP

#include "render/Renderable.hpp"
#include "render/Light.hpp"
#include "scene/Camera.hpp"

#include <vector>

class Renderer {
public:
    Renderer();
    Renderer(glm::vec2 size);

    virtual void prepare();
    void registerRenderable(std::shared_ptr<Renderable> renderable);
    void registerLight(std::shared_ptr<Light> light);
    void setSize(glm::vec2 size);
    void setCamera(std::shared_ptr<Camera> camera);
    virtual void render() = 0;
    virtual void cleanup();

protected:
    virtual void onResize(glm::vec2 size);

	std::vector<std::shared_ptr<Light>> mLights;
    std::vector<std::shared_ptr<Renderable>> mRenderables;
    std::shared_ptr<Camera> mCamera;
    glm::vec2 mSize;

};

#endif
