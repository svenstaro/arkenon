#include "Node.hpp"

Node::Node(const std::string& name, Node::RenderTechnique render_technique)
    : position(0.f, 0.f, 0.f),
      scale(1.f, 1.f, 1.f),
      mRenderTechnique(render_technique)
{
    mName = name;
}

std::shared_ptr<Node> Node::addChild(std::shared_ptr<Node> node)
{
    std::cout << "Appending node: " << getName() << " > " << node->getName() << std::endl;
    mChildren[node->getName()] = node;
    addInputForwarding(node.get());
    node->mParent = this;
    return node;
}

std::shared_ptr<Node> Node::getChild(const std::string& name)
{
    if(mChildren.count(name) == 0) std::cout << "Warning: Node \"" << name << "\" is no child of node \"" << mName << "\"." << std::endl;
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

Node* Node::getParent() const
{
    return mParent;
}

const std::map<std::string, std::shared_ptr<Node> >& Node::getChildren() const
{
    return mChildren;
}

bool Node::isVisible() const
{
    return true;
}

void Node::onPrepareRender() {}

std::shared_ptr<Material> Node::getMaterial()
{
    return nullptr;
}

glm::mat4 Node::getModelMatrix() const
{
    return getAbsoluteTransformationMatrix();
}

void Node::draw()
{
    if(mRenderTechnique != None)
    {
        std::cerr << "Renderable node should implement the draw() method." << std::endl;
        std::cout << getName() << std::endl;
    }
}

void Node::setRenderTechnique(Node::RenderTechnique render_technique)
{
    mRenderTechnique = render_technique;
}

Node::RenderTechnique Node::getRenderTechnique() const
{
    return mRenderTechnique;
}
