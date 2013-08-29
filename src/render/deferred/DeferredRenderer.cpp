#include "DeferredRenderer.hpp"

#include "util/check.hpp"
#include "render/Shape3D.hpp"

DeferredRenderer::DeferredRenderer(glm::vec2 size)
    : mSize(size),
      mGBuffer(size, 3, GL_RGB16F),
      mLightsBuffer(size),
      mGeometryPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.geometry.vertex.glsl", "data/shader/deferred.geometry.fragment.glsl", false)),
      mLightPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.light.vertex.glsl", "data/shader/deferred.light.fragment.glsl"))
{
    glBindFragDataLocation(mGeometryPassShader->getHandle(), 0, "color");
    glBindFragDataLocation(mGeometryPassShader->getHandle(), 1, "position");
    glBindFragDataLocation(mGeometryPassShader->getHandle(), 2, "normal");
    mGeometryPassShader->link();
}

void DeferredRenderer::render()
{
    Framebuffer::unbind();
    mGBuffer.bindDraw(3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _geometryPass();

    Framebuffer::unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //_debugOutput(0, Rect(0, 0.5, 0.5, 0.5));
    //_debugOutput(1, Rect(0.5, 0.5, 0.5, 0.5));
    //_debugOutput(2, Rect(0, 0, 0.5, 0.5));

    _lightPass();
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

    mGeometryPassShader->link();


    for(auto iter = mRenderables.begin(); iter != mRenderables.end(); iter++) {
        mGeometryPassShader->send("MVP", mCamera->getViewProjectionMatrix() * (*iter)->getModelMatrix());
        mGeometryPassShader->send("M", (*iter)->getModelMatrix());
        mGeometryPassShader->send("diffuse_texture", (*iter)->getDiffuseTexture());
        (*iter)->draw();
    }
}

void DeferredRenderer::_lightPass()
{
    // Enable depth test
    glDisable(GL_DEPTH_TEST);

    // Disable blending
    glEnable(GL_BLEND);

    // Diffuse pass
    mLightPassShader->use();

    // texture slots
    mGBuffer.bindRead(3);
    mLightPassShader->send("colorMap", mGBuffer.getTexture(0), 0);
    mLightPassShader->send("positionMap", mGBuffer.getTexture(1), 1);
    mLightPassShader->send("normalMap", mGBuffer.getTexture(2), 2);

    mLightPassShader->send("screenSize", mSize);
    mLightPassShader->send("lightPosition", mPointLight1.position);
    mLightPassShader->send("lightColor", mPointLight1.color);
    mLightPassShader->send("lightRadius", mPointLight1.radius);

    Shape3D sphere("light-volume-sphere");
    sphere.makeUvSphere(16, 16);
    sphere.position = mPointLight1.position;
    sphere.scale = glm::vec3(mPointLight1.radius);
    mLightPassShader->send("MVP", mCamera->getViewProjectionMatrix() * sphere.getModelMatrix());
    mLightPassShader->send("VP", mCamera->getViewProjectionMatrix());
    mLightPassShader->send("M", sphere.getModelMatrix());
    sphere.draw();
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
