#include "ForwardRenderer.hpp"

#include "util/check.hpp"

ForwardRenderer::ForwardRenderer()
    : mColorPassShader(std::make_shared<ShaderProgram>("data/shader/simple.vertex.glsl", "data/shader/simple.fragment.glsl")),
      mLightPassShader(std::make_shared<ShaderProgram>("data/shader/light.vertex.glsl", "data/shader/light.fragment.glsl"))
{}

void ForwardRenderer::render()
{
    // Enable depth buffer
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDepthMask(GL_TRUE);
    glClearDepth(1.0);
    GL_CHECK();

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GL_CHECK();

    // diffuse pass
    mColorPassShader->use();
    mColorPassShader->send("ambient_light", glm::vec4(1.f, 1.f, 1.f, 1.f));
    for(auto iter = mRenderNodes.begin(); iter != mRenderNodes.end(); iter++) {
        mColorPassShader->send("MVP", mCamera->getViewProjectionMatrix() * (*iter)->getModelMatrix());
        mColorPassShader->send("diffuse_texture", (*iter)->getMaterial()->getDiffuseTexture());
        (*iter)->draw();
    }

    // TODO; render the light on top
}
