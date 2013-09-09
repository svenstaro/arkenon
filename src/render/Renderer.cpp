#include "Renderer.hpp"

Renderer::Renderer()
{}

Renderer::Renderer(glm::vec2 size)
    : mSize(size)
{}

void Renderer::prepare()
{}

void Renderer::registerRenderable(std::shared_ptr<Renderable> renderable)
{
    mRenderables.push_back(renderable);
}

void Renderer::registerLight(std::shared_ptr<Light> light) {
    mLights.push_back(light);
}

void Renderer::setSize(glm::vec2 size)
{
    if(mSize.x == size.x && mSize.y == size.y) return;

    mSize = size;
    onResize(mSize);
}

void Renderer::setCamera(std::shared_ptr<Camera> camera)
{
    mCamera = camera;
}

void Renderer::cleanup()
{
    mRenderables.clear();
    mLights.clear();
}

void Renderer::onResize(glm::vec2 size)
{}
