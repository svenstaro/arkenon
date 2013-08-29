#include "DeferredRenderer.hpp"

#include "util/check.hpp"

DeferredRenderer::DeferredRenderer(glm::vec2 size)
    : mSize(size),
      mGBuffer(size, 3, GL_RGB16F),
      mLightsBuffer(size),
      mGeometryPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.geometry.vertex.glsl", "data/shader/deferred.geometry.fragment.glsl")),
      mLightPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.light.vertex.glsl", "data/shader/deferred.light.fragment.glsl"))
{
}

void DeferredRenderer::render()
{
    Framebuffer::unbind();
    mGBuffer.bindDraw(3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _geometryPass();

    Framebuffer::unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _debugOutput(0, Rect(0, 0.5, 0.5, 0.5));
    _debugOutput(1, Rect(0.5, 0.5, 0.5, 0.5));
    _debugOutput(2, Rect(0, 0, 0.5, 0.5));
//    _lightPass();
//    _finalPass();

}

void DeferredRenderer::_geometryPass()
{
    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0);

    // Disable blending
    glDisable(GL_BLEND);

    // Diffuse pass
    mGeometryPassShader->use();

    // texture slots
    int buffers[] = {0, 1, 2};
    mGBuffer.bindDraw(3, buffers);
    mGeometryPassShader->send("color", 0);
    mGeometryPassShader->send("position", 1);
    mGeometryPassShader->send("normal", 2);
    for(auto iter = mRenderables.begin(); iter != mRenderables.end(); iter++) {
        mGeometryPassShader->send("MVP", mCamera->getViewProjectionMatrix() * (*iter)->getModelMatrix());
        mGeometryPassShader->send("M", (*iter)->getModelMatrix());
        mGeometryPassShader->send("diffuse_texture", (*iter)->getDiffuseTexture());
        mGeometryPassShader->send("ambient_light", glm::vec4(1.f, 1.f, 1.f, 1.f));
        (*iter)->draw();
    }
}

void DeferredRenderer::_lightPass()
{

}

void DeferredRenderer::_debugOutput(int n, const Rect& subrect)
{
    Framebuffer::unbind(GL_DRAW_FRAMEBUFFER);   // draw to screen
    mGBuffer.bindRead(n);                       // read from gbuffer
    glm::vec2 from = mSize * subrect.position;
    glm::vec2 to = from + mSize * subrect.size;
    glBlitFramebuffer(0, 0, mSize.x, mSize.y,
                      from.x, from.y, to.x, to.y,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void DeferredRenderer::_finalPass()
{

}
