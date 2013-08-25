#ifndef _RENDER_FORWARDRENDERER_HPP
#define _RENDER_FORWARDRENDERER_HPP

#include "render/Renderer.hpp"
#include "render/ShaderProgram.hpp"

class ForwardRenderer : public Renderer {
public:
    ForwardRenderer();
    virtual void render();

private:
    std::shared_ptr<ShaderProgram> mColorPassShader;
    std::shared_ptr<ShaderProgram> mLightPassShader;

};

#endif
