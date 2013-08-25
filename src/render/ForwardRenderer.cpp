#include "ForwardRenderer.hpp"

#include "utils.hpp"

ForwardRenderer::ForwardRenderer()
{
    mColorPassShader = std::make_shared<ShaderProgram>();
    Shader simple_vertex(Shader::Vertex, "data/shader/simple.vertex.glsl");
    Shader simple_fragment(Shader::Fragment, "data/shader/simple.fragment.glsl");
    mColorPassShader->attach(simple_vertex);
    mColorPassShader->attach(simple_fragment);
    mColorPassShader->link();

    mLightPassShader = std::make_shared<ShaderProgram>();
    Shader light_vertex(Shader::Vertex, "data/shader/light.vertex.glsl");
    Shader light_fragment(Shader::Fragment, "data/shader/light.fragment.glsl");
    mLightPassShader->attach(light_vertex);
    mLightPassShader->attach(light_fragment);
    mLightPassShader->link();
}

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
    for(auto iter = mRenderables.begin(); iter != mRenderables.end(); iter++) {
        (*iter)->render(mCamera, mColorPassShader);
    }

    // TODO; render the light on top
}
