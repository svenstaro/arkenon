#include "Renderer.hpp"

Renderer::Renderer()
{}

Renderer::Renderer(glm::vec2 size)
    : mSize(size)
{}

void Renderer::prepare()
{}

void Renderer::prepareScene(Node* node, Node::RenderTechnique render_technique)
{
    if(!node->isVisible()) return;

    if(node->getRenderTechnique() == render_technique) {
        registerRenderNode(node);
    }
    node->onPrepareRender();

    for(auto& iter : node->getChildren()) {
        prepareScene(iter.second.get(), render_technique);
    }
}

void Renderer::registerRenderNode(Node* node) {
    mRenderNodes.push_back(node);
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
    mRenderNodes.clear();
    mLights.clear();
}

void Renderer::onResize(glm::vec2 size)
{}
