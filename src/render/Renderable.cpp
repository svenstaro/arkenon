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


std::shared_ptr<Material> Renderable::getMaterial()
{
    return nullptr;
}

