#include "DeferredRenderer.hpp"

#include "util/check.hpp"

DeferredRenderer::DeferredRenderer(glm::vec2 size)
    : Renderer(size),
      mGBuffer(size, 4, true, GL_RGBA16F),
      mLightsBuffer(size, 2, false, GL_RGB),
      mShadowBuffer(size, 1, false, GL_R32F, GL_RED),
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

    GL_CHECK();


}

void DeferredRenderer::render()
{
    geometryPass();
    //debugOutput(2); return;
    lightPass();
    //ssaoPass();
    finalPass();
}

void DeferredRenderer::onResize(glm::vec2 size)
{
    mGBuffer = Framebuffer(size, 4, true, GL_RGBA16F);
    mLightsBuffer = Framebuffer(size, 2, false, GL_RGB);
    mShadowBuffer = Framebuffer(size, 1, false, GL_R32F, GL_RED);
}

void DeferredRenderer::geometryPass()
{
    // prepare framebuffer
    mGBuffer.bindDraw(4);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Enable depth test
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0);

    // Disable blending
    glDisable(GL_BLEND);



    // Diffuse pass
    mGeometryPassShader->use();

    mGeometryPassShader->send("color", 0);
    mGeometryPassShader->send("position", 1);
    mGeometryPassShader->send("normal", 2);
    mGeometryPassShader->send("specular", 3);

    for(auto iter = mRenderables.begin(); iter != mRenderables.end(); iter++) {

        glm::mat4 m = (*iter)->getModelMatrix();
        glm::mat4 mv = mCamera->getViewMatrix() * (*iter)->getModelMatrix();
        glm::mat4 mvp = mCamera->getViewProjectionMatrix() * m;
        glm::mat3 normalMatrix = glm::mat3(m);

        mGeometryPassShader->send("MVP", mvp);
        mGeometryPassShader->send("MV", mv);
        mGeometryPassShader->send("M", m);
        mGeometryPassShader->send("M3x3", normalMatrix);

        std::shared_ptr<Material> material = (*iter)->getMaterial();

        if(material)
        {
            mGeometryPassShader->send("diffuseColor", material->getDiffuseColor());
            mGeometryPassShader->send("diffuseTexture", material->getDiffuseTexture(), 0);
            mGeometryPassShader->send("normalTexture", material->getNormalTexture(), 1);
            mGeometryPassShader->send("hasNormalTexture", material->getNormalTexture() ? 1 : 0);
            mGeometryPassShader->send("specularTexture", material->getSpecularTexture(), 2);
            mGeometryPassShader->send("specularShininess", material->getSpecularShininess());
            mGeometryPassShader->send("specularColorMix", material->getSpecularColorMix());
        }
        (*iter)->draw();
    }
}

void DeferredRenderer::lightPass()
{
    // prepare framebuffer
    mLightsBuffer.bindDraw(2);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
    mLightPassShader->send("screenSize", mSize);
    mLightPassShader->send("VP", mCamera->getViewProjectionMatrix());
    mLightPassShader->send("cameraPosition", mCamera->getAbsolutePosition());

    // texture slots
    mLightPassShader->send("positionMap", mGBuffer.getTexture(1), 0);
    mLightPassShader->send("normalMap", mGBuffer.getTexture(2), 1);
    mLightPassShader->send("specularMap", mGBuffer.getTexture(3), 2);

    mGeometryPassShader->send("out_colorMultiply", 0);
    mGeometryPassShader->send("out_colorAdd", 1);

    for(auto iter = mLights.begin(); iter != mLights.end(); iter++) {
        glm::vec3 position = (*iter)->getAbsolutePosition();
        float radius = (*iter)->getRadius();

        mLightPassShader->send("lightPosition", position);
        mLightPassShader->send("lightColor", (*iter)->getColor());
        mLightPassShader->send("lightRadius", radius);

        mSphere.position = position;
        mSphere.scale = glm::vec3(radius);
        mLightPassShader->send("MVP", mCamera->getViewProjectionMatrix() * mSphere.getModelMatrix());
        mSphere.draw();
    }

    glDisable(GL_CULL_FACE);
}

void DeferredRenderer::ssaoPass() {
    /*
    // prepare framebuffer
    mShadowBuffer.bindDraw();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDisable(GL_DEPTH_TEST);

    mAOPassShader->use();

    glm::mat4 projMatrix = glm::ortho<GLfloat>(-1.0, 1.0, 1.0, -1.0, -1.0, 1.0);
    mAOPassShader->send("projMatrix", projMatrix);

    //mAOPassShader->send("depthTexture", mGBuffer.getTexture(3), 0);
    mAOPassShader->send("normalTexture", mGBuffer.getTexture(2), 1);
    //mAOPassShader->send("randomTexture", mRandomTexture, 2);

    mFullQuad.draw();
    */
}

void DeferredRenderer::debugOutput(int n, const Rect& subrect)
{
    Framebuffer::unbind(GL_DRAW_FRAMEBUFFER);   // draw to screen
    mGBuffer.bindRead(n);                       // read from gbuffer
    glm::vec2 from = mSize * subrect.position;
    glm::vec2 to = from + mSize * subrect.size;
    glBlitFramebuffer(0, 0, mSize.x, mSize.y,
                      from.x, from.y, to.x, to.y,
                      GL_COLOR_BUFFER_BIT, GL_LINEAR);
}

void DeferredRenderer::finalPass()
{
    Framebuffer::unbind();

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

    mFinalPassShader->use();

    mFinalPassShader->send("diffuseMap", mGBuffer.getTexture(0), 0);
    mFinalPassShader->send("lightMapMultiply", mLightsBuffer.getTexture(0), 1);
    mFinalPassShader->send("lightMapAdd", mLightsBuffer.getTexture(1), 2);
    //mFinalPassShader->send("shadowMap", mShadowBuffer.getTexture(), 2);
    //mFinalPassShader->send("lambertMap", mLambertTexture, 3);

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
