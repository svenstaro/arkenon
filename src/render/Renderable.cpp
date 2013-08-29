#include "Renderable.hpp"

Renderable::~Renderable()
{}


RenderableNode::RenderableNode(const std::string& name)
    : Node(name),
      Renderable()
{}

glm::mat4 RenderableNode::getModelMatrix() const {
    return getAbsoluteTransformationMatrix();
}


std::shared_ptr<Texture> Renderable::getDiffuseTexture()
{
    return nullptr;
}

std::shared_ptr<Texture> Renderable::getNormalTexture()
{
    return nullptr;
}

