#include "Node.hpp"

Node::Node(const std::string& name)
    : position(0.f, 0.f, 0.f),
      scale(1.f, 1.f, 1.f)
{
    mName = name;
}

std::shared_ptr<Node> Node::addChild(std::shared_ptr<Node> node)
{
    mChildren[node->getName()] = node;
    addInputForwarding(node.get());
    node->mParent = this;
    return node;
}

std::shared_ptr<Node> Node::getChild(const std::string& name)
{
    return mChildren[name];
}

const std::string& Node::getName() const
{
    return mName;
}

glm::vec3 Node::getAbsolutePosition() const
{
    if(mParent)
        return mParent->position + position;
    else
        return position;
}

glm::quat Node::getAbsoluteRotation() const
{
    if(mParent)
        return rotation * mParent->rotation;
    else
        return rotation;
}

glm::vec3 Node::getAbsoluteScale() const
{
    if(mParent)
        return scale * mParent->scale;
    else
        return scale;
}

glm::mat4 Node::getTransformationMatrix() const
{
    return glm::translate(position) * glm::mat4_cast(rotation) * glm::scale(scale);
}

glm::mat4 Node::getAbsoluteTransformationMatrix() const
{
    if(mParent)
        return mParent->getAbsoluteTransformationMatrix() * getTransformationMatrix();
    else
        return getTransformationMatrix();
}

void Node::setAbsolutePosition(const glm::vec3& absolute_position)
{
    if(mParent)
        position = absolute_position - mParent->position;
    else
        position = absolute_position;
}

// q2 = r*q1            local = absolute * parent'
// r  = q2*q1'          absolute = local * parent
void Node::setAbsoluteRotation(const glm::quat& absolute_rotation)
{
    if(mParent)
        rotation = absolute_rotation * glm::inverse(mParent->rotation);
    else
        rotation = absolute_rotation;
}

const Node* Node::getParent() const
{
    return mParent;
}

