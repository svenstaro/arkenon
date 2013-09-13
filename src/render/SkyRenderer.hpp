#ifndef _RENDER_SKYRENDERER_HPP
#define _RENDER_SKYRENDERER_HPP

#include "render/Renderer.hpp"
#include "render/ShaderProgram.hpp"
#include "render/Shape2D.hpp"
#include "render/Shape3D.hpp"

class SkyRenderer : public Renderer {
public:
    SkyRenderer(glm::vec2 size);
    virtual void render();

private:
    std::shared_ptr<ShaderProgram> mShader;
    VertexBuffer mFullQuad;
    Shape3D mSphere;

};

#endif
