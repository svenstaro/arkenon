#include "Renderer.hpp"

void Renderer::prepare()
{}

void Renderer::registerRenderable(std::shared_ptr<Renderable> renderable)
{
    mRenderables.push_back(renderable);
}

void Renderer::setCamera(std::shared_ptr<Camera> camera)
{
    mCamera = camera;
}

void Renderer::cleanup()
{
    mRenderables.clear();
}
