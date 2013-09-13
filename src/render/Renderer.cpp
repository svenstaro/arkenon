#include "Renderer.hpp"

Renderer::Renderer()
{}

Renderer::Renderer(glm::vec2 size)
    : mSize(size)
{}

void Renderer::prepare()
{}

void Renderer::prepareScene(Node* node)
{
    if(node->isRenderable()) {
        registerRenderable(dynamic_cast<Renderable*>(node));
    }
    node->onPrepareRender();

    for(auto& iter : node->getChildren()) {
        prepareScene(iter.second.get());
    }
}

void Renderer::registerRenderable(std::shared_ptr<Node> renderable)
{
    registerRenderable(dynamic_cast<Renderable*>(renderable.get()));
}

void Renderer::registerRenderable(Renderable* renderable)
{
    mRenderables.push_back(renderable);
}

void Renderer::registerLight(std::shared_ptr<Node> light) {
    registerLight(dynamic_cast<Light*>(light.get()));
}

void Renderer::registerLight(Light* light) {
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
