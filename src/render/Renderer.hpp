#ifndef _RENDER_RENDERER_HPP
#define _RENDER_RENDERER_HPP

#include "render/Renderable.hpp"
#include "render/Light.hpp"
#include "scene/Camera.hpp"

#include <vector>

class Renderer {
public:
    virtual void prepare();
    void registerRenderable(std::shared_ptr<Renderable> renderable);
    void registerLight(std::shared_ptr<Light> light);
    void setCamera(std::shared_ptr<Camera> camera);
    virtual void render() = 0;
    virtual void cleanup();

protected:
	std::vector<std::shared_ptr<Light>> mLights;
    std::vector<std::shared_ptr<Renderable>> mRenderables;
    std::shared_ptr<Camera> mCamera;

};

#endif
