#include "RenderableNode.hpp"

RenderableNode::RenderableNode(const std::string& name)
    : Node(name),
      Renderable()
{}

glm::mat4 RenderableNode::getModelMatrix() const {
    return getAbsoluteTransformationMatrix();
}

bool RenderableNode::isRenderable() const
{
    return true;
}
