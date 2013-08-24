#include "Node.hpp"

Node::Node(const std::string& name)
{
    mName = name;
}

Node* Node::addChild(Node* node)
{
    const std::string& name = node->getName();
    mChildren[name] = std::unique_ptr<Node>(std::move(node));
    Node* n = mChildren[name].get();
    n->mParent = this;
    return n;
}

Node* Node::getChild(const std::string& name)
{
    return mChildren[name].get();
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

glm::mat4 Node::getTransformationMatrix() const
{
    // TODO: scale
    return glm::translate(position) * glm::mat4_cast(rotation);
}

glm::mat4 Node::getAbsoluteTransformationMatrix() const
{
    if(mParent)
        return getTransformationMatrix() * mParent->getAbsoluteTransformationMatrix();
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

