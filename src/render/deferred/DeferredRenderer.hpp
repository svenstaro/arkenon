#ifndef _RENDER_DEFERRED_DEFERREDRENDERER_HPP
#define _RENDER_DEFERRED_DEFERREDRENDERER_HPP

#include <memory>

#include "render/Renderer.hpp"
#include "render/ShaderProgram.hpp"
#include "render/Framebuffer.hpp"
#include "util/Rect.hpp"

struct PointLight {
    PointLight(const glm::vec3& p = glm::vec3(4, 4, 0), float r = 12.f, const glm::vec4& c = glm::vec4(1, 1, 1, 1))
        : position(p), radius(r), color(c) {}

    glm::vec3 position;
    float radius;
    glm::vec4 color;
};

class DeferredRenderer : public Renderer {
public:
    DeferredRenderer(glm::vec2 size);
    virtual void render();

private:
    void _geometryPass();
    void _lightPass();

    /**
     * Blits GBuffer Texture to screen
     * @param n The number of the texture to blit.
     */
    void _debugOutput(int n, const Rect& subrect = Rect(0, 0, 1, 1));

    void _finalPass();

    PointLight mPointLight1;
    glm::vec2 mSize;

    Framebuffer mGBuffer;       //< MRT#3: color, position, normal;         GL_RGB16F
    Framebuffer mLightsBuffer;  //< no MRT, just ADD-blend all the lights   GL_RGB

    std::shared_ptr<ShaderProgram> mGeometryPassShader;
    std::shared_ptr<ShaderProgram> mLightPassShader;

};

#endif
