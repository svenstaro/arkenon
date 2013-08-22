#include "ForwardRenderer.hpp"

ForwardRenderer::ForwardRenderer()
{
    Shader simple_vertex(Shader::Vertex, "data/shader/simple.vertex.glsl");
    Shader simple_fragment(Shader::Fragment, "data/shader/simple.fragment.glsl");
    mShaderColor.attach(simple_vertex);
    mShaderColor.attach(simple_fragment);
    mShaderColor.link();

    Shader light_vertex(Shader::Vertex, "data/shader/light.vertex.glsl");
    Shader light_fragment(Shader::Fragment, "data/shader/light.fragment.glsl");
    mShaderLighting.attach(light_vertex);
    mShaderLighting.attach(light_fragment);
    mShaderLighting.link();
}

void ForwardRenderer::render()
{
    //mShaderColor.send("ambient_light", glm::vec4(0.5, 0.8, 0.5, 1.f));
    mShaderLighting.send("light_color", glm::vec4(0.5, 1.f, 0.5, 1.f));
    mShaderLighting.send("light_position", glm::vec3(-2, 2, -2));
    mShaderLighting.send("light_size", 10.f);

    // color pass
    for(auto iter = mMeshes.begin(); iter != mMeshes.end(); iter++) {
        (*iter)->render(mCamera, &mShaderLighting);
    }

    // render the light on top
}
