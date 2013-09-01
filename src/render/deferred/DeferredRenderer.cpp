#include "DeferredRenderer.hpp"

#include "util/check.hpp"

DeferredRenderer::DeferredRenderer(glm::vec2 size)
    : mSize(size),
      mGBuffer(size, 3, GL_RGB16F),
      mLightsBuffer(size),
      mSphere("light-volume-sphere"),
      mGeometryPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.geometry.vertex.glsl", "data/shader/deferred.geometry.fragment.glsl")),
      mLightPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.light.vertex.glsl", "data/shader/deferred.light.fragment.glsl"))
{
    mSphere.makeUvSphere(16, 16);
}

void DeferredRenderer::render()
{
    Framebuffer::unbind();
    mGBuffer.bindDraw(3);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _geometryPass();

    Framebuffer::unbind();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    _lightPass();
    _finalPass();
}

void DeferredRenderer::setSize(glm::vec2 size)
{
    if(mSize.x == size.x && mSize.y == size.y) return;

    mSize = size;
    mGBuffer = Framebuffer(size, 3, GL_RGB16F);
    mLightsBuffer = Framebuffer(size);
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
        std::shared_ptr<Material> material = (*iter)->getMaterial();
        mGeometryPassShader->send("MVP", mCamera->getViewProjectionMatrix() * (*iter)->getModelMatrix());
        mGeometryPassShader->send("M", (*iter)->getModelMatrix());
        if(material)
        {
            mGeometryPassShader->send("diffuseColor", material->getDiffuseColor());
            mGeometryPassShader->send("diffuseTexture", material->getDiffuseTexture());
            mGeometryPassShader->send("normalTexture", material->getNormalTexture(), 1);
        }
        (*iter)->draw();
    }
}

void DeferredRenderer::_lightPass()
{
    // Disable depth test
    glDisable(GL_DEPTH_TEST);

    // Enable blending
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

    // Diffuse pass
    mLightPassShader->use();

    // texture slots
    mGBuffer.bindRead(3);
    mLightPassShader->send("colorMap", mGBuffer.getTexture(0), 0);
    mLightPassShader->send("positionMap", mGBuffer.getTexture(1), 1);
    mLightPassShader->send("normalMap", mGBuffer.getTexture(2), 2);

    mLightPassShader->send("screenSize", mSize);

    for(auto iter = mLights.begin(); iter != mLights.end(); iter++) {
        glm::vec3 position = (*iter)->getAbsolutePosition();
        float radius = (*iter)->getRadius();

        mLightPassShader->send("lightPosition", position);
        mLightPassShader->send("lightColor", (*iter)->getColor());
        mLightPassShader->send("lightRadius", radius);

        mSphere.position = position;
        mSphere.scale = glm::vec3(radius);
        mLightPassShader->send("MVP", mCamera->getViewProjectionMatrix() * mSphere.getModelMatrix());
        mLightPassShader->send("VP", mCamera->getViewProjectionMatrix());
        mLightPassShader->send("M", mSphere.getModelMatrix());
        mSphere.draw();
    }

    glDisable(GL_CULL_FACE);
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
    // Copy the depth buffer
    mGBuffer.bindRead();
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    glBlitFramebuffer(0, 0, mSize.x, mSize.y,
                      0, 0, mSize.x, mSize.y,
                      GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST);
}
