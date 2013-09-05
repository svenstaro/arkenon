#include "DeferredRenderer.hpp"

#include "util/check.hpp"

DeferredRenderer::DeferredRenderer(glm::vec2 size)
    : mSize(size),
      mGBuffer(size, 3, true, GL_RGBA16F, GL_RGBA, GL_HALF_FLOAT),
      mLightsBuffer(size),
      //mShadowBuffer(size, 1, false, GL_R32F , GL_RED),
      mSphere("light-volume-sphere"),
      mQuad("fullsceen-quad"),
      //mAOPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.final.vertex.glsl", "data/shader/deferred.ssao.fragment.glsl")),
      mGeometryPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.geometry.vertex.glsl", "data/shader/deferred.geometry.fragment.glsl")),
      mLightPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.light.vertex.glsl", "data/shader/deferred.light.fragment.glsl")),
      mFinalPassShader(std::make_shared<ShaderProgram>("data/shader/deferred.final.vertex.glsl", "data/shader/deferred.final.fragment.glsl"))
{
    mSphere.makeUvSphere(16, 16);
    mQuad.makeRectangle(glm::vec2(1.0, 1.0), Rect(-1.0, -1.0, 1.0, 1.0));

    mFullQuad.clear();
    mFullQuad.addQuad(
        Vertex(-1, -1, 0, 0, 1),
        Vertex( 1, -1, 0, 1, 1),
        Vertex( 1,  1, 0, 1, 0), 
        Vertex(-1,  1, 0, 0, 0) 
    );
    mFullQuad.commit();

    mLambertTexture = std::make_shared<Texture>();
    mLambertTexture->load("data/gfx/lambertMap.png");
    mLambertTexture->setSmooth(false);

    mRandomTexture = std::make_shared<Texture>();
    mRandomTexture->load("data/gfx/AONoise.png");
    mRandomTexture->setSmooth(false);
    GL_CHECK();


}

void DeferredRenderer::render()
{


    Framebuffer::unbind();

    mGBuffer.bindDraw(3);
    GL_CHECK();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _geometryPass();

    //Framebuffer::unbind(GL_READ_FRAMEBUFFER);
    mLightsBuffer.bindDraw();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    _lightPass();

    //mShadowBuffer.bindDraw();
    //glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //_ssaoPass();

    Framebuffer::unbind();
    _finalPass();

    //_debugOutput(1);
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
    //int buffers[] = {0, 1, 2};
    //mGBuffer.bindDraw(3, buffers);

    mGeometryPassShader->send("color", 0);
    mGeometryPassShader->send("position", 1);
    mGeometryPassShader->send("normal", 2);

    for(auto iter = mRenderables.begin(); iter != mRenderables.end(); iter++) {

        glm::mat4 m = (*iter)->getModelMatrix();
        glm::mat4 mv = mCamera->getViewMatrix() * (*iter)->getModelMatrix();
        glm::mat4 mvp = mCamera->getViewProjectionMatrix() * m;
        glm::mat4 normalMatrix = glm::transpose(glm::inverse(mv));

        mGeometryPassShader->send("MVP", mvp);
        mGeometryPassShader->send("MV", mv);
        mGeometryPassShader->send("M", m);
        mGeometryPassShader->send("normalMatrix", normalMatrix);

        std::shared_ptr<Material> material = (*iter)->getMaterial();

        if(material)
        {
            mGeometryPassShader->send("diffuseColor", material->getDiffuseColor());
            mGeometryPassShader->send("diffuseTexture", material->getDiffuseTexture(), 0);
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
    //mLightPassShader->send("colorMap", mGBuffer.getTexture(0), 0);
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

void DeferredRenderer::_ssaoPass() {
    glDisable(GL_DEPTH_TEST);
    mAOPassShader->use();



    glm::mat4 projMatrix = glm::ortho<GLfloat>(-1.0, 1.0, 1.0, -1.0, -1.0, 1.0);
    mAOPassShader->send("projMatrix", projMatrix);

    //mAOPassShader->send("depthTexture", mGBuffer.getTexture(3), 0);
    mAOPassShader->send("normalTexture", mGBuffer.getTexture(2), 1);
    mAOPassShader->send("randomTexture", mRandomTexture, 2);

    mFullQuad.draw();
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
    glDisable(GL_DEPTH_TEST);
    glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);

    mFinalPassShader->use();

    mFinalPassShader->send("diffuseMap", mGBuffer.getTexture(0), 0);
    mFinalPassShader->send("lightMap", mLightsBuffer.getTexture(), 1);
    //mFinalPassShader->send("shadowMap", mShadowBuffer.getTexture(), 2);
    mFinalPassShader->send("lambertMap", mLambertTexture, 3);

    //TODO: Move this maybe
    glm::mat4 projMatrix = glm::ortho<GLfloat>(-1.0, 1.0, 1.0, -1.0, -1.0, 1.0);
    mFinalPassShader->send("projMatrix", projMatrix);
    mFullQuad.draw();
    
    //Copy Deth Buffer
    mGBuffer.bindRead();
    glBlitFramebuffer(0, 0, mSize.x, mSize.y,
                      0, 0, mSize.x, mSize.y,
                      GL_DEPTH_BUFFER_BIT,
                      GL_NEAREST);
    
}
