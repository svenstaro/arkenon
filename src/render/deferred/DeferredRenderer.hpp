#ifndef _RENDER_DEFERRED_DEFERREDRENDERER_HPP
#define _RENDER_DEFERRED_DEFERREDRENDERER_HPP

#include <memory>

#include "render/Renderer.hpp"
#include "render/ShaderProgram.hpp"
#include "render/Framebuffer.hpp"
#include "util/Rect.hpp"
#include "render/Shape2D.hpp"
#include "render/Shape3D.hpp"

class DeferredRenderer : public Renderer {
public:
    DeferredRenderer(glm::vec2 size);
    virtual void render();

    void setSize(glm::vec2 size);

private:
    void geometryPass();
    void lightPass();
    void ssaoPass();
    void finalPass();

    /**
     * Blits GBuffer Texture to screen
     * @param n The number of the texture to blit.
     */
    void debugOutput(int n, const Rect& subrect = Rect(0, 0, 1, 1));

    Shape3D mSphere;
    Shape2D mQuad;

    VertexBuffer mFullQuad;

    glm::vec2 mSize;

    Framebuffer mGBuffer;       //< MRT#3: color, position, normal, material;                       GL_RGB16F
                                //  material: r=specular intensity, g=specular shininess, b=mix(light color, white, ??)
    Framebuffer mLightsBuffer;  //< MRT#2: multiply-component, add-component; ADD them together;    GL_RGB
    Framebuffer mShadowBuffer;

    std::shared_ptr<ShaderProgram> mGeometryPassShader;
    std::shared_ptr<ShaderProgram> mLightPassShader;
    std::shared_ptr<ShaderProgram> mFinalPassShader;
};

#endif
