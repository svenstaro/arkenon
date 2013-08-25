#ifndef _RENDER_FLATRENDERER_HPP
#define _RENDER_FLATRENDERER_HPP

#include "render/Renderer.hpp"
#include "render/ShaderProgram.hpp"

#include <memory>

class FlatRenderer : public Renderer {
public:
    FlatRenderer();
    void render();

private:
    std::shared_ptr<ShaderProgram> mShader;
};

#endif
