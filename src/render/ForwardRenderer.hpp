#ifndef _RENDER_FORWARDRENDERER_HPP
#define _RENDER_FORWARDRENDERER_HPP

#include "render/Renderer.hpp"


class ForwardRenderer : public Renderer {
public:
    ForwardRenderer();
    virtual void render();

private:
    ShaderProgram mShaderColor;
    ShaderProgram mShaderLighting;

};

#endif
