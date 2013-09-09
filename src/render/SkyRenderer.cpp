#include "SkyRenderer.hpp"

#include "util/check.hpp"

SkyRenderer::SkyRenderer(glm::vec2 size)
    : Renderer(size),
      mShader(std::make_shared<ShaderProgram>("data/shader/simple.vertex.glsl", "data/shader/sky.fragment.glsl")),
      mSphere("skysphere")
{
    mFullQuad.clear();
    mFullQuad.addQuad(
        Vertex(-1, -1, 0, 0, 1),
        Vertex( 1, -1, 0, 1, 1),
        Vertex( 1,  1, 0, 1, 0),
        Vertex(-1,  1, 0, 0, 0)
    );
    mFullQuad.commit();

    mSphere.makeUvSphere(20, 40);
}


void SkyRenderer::render()
{
    glDisable(GL_DEPTH_TEST);
    glDisable(GL_BLEND);
    GL_CHECK();

    mSphere.position = mCamera->getAbsolutePosition();

    mShader->use();
    mShader->send("MVP", mCamera->getViewProjectionMatrix() * mSphere.getModelMatrix());
    mShader->send("size", mSize);
    mShader->send("VP", mCamera->getViewProjectionMatrix());

    mSphere.draw();
}
