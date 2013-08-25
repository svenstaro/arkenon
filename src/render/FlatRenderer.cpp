#include "FlatRenderer.hpp"

#include "utils.hpp"

FlatRenderer::FlatRenderer()
{
    mShader = std::make_shared<ShaderProgram>();
    Shader vertex(Shader::Vertex, "data/shader/simple.vertex.glsl");
    Shader fragment(Shader::Fragment, "data/shader/simple.fragment.glsl");
    mShader->attach(vertex);
    mShader->attach(fragment);
    mShader->link();
}

void FlatRenderer::render()
{
    // Disable depth buffer
    glDisable(GL_DEPTH_TEST);
    GL_CHECK();

    // Enable blending
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    GL_CHECK();

    mShader->use();
    mShader->send("ambient_light", glm::vec4(1.f, 1.f, 1.f, 1.f));

    for(auto iter = mRenderables.begin(); iter != mRenderables.end(); iter++) {
        (*iter)->render(mCamera, mShader);
    }
}
