#ifndef _RENDER_RENDERABLENODE_HPP
#define _RENDER_RENDERABLENODE_HPP

#include "scene/Node.hpp"
#include "render/Renderable.hpp"

class RenderableNode : public Node, public Renderable {
public:
    RenderableNode(const std::string& name);
    glm::mat4 getModelMatrix() const;

    virtual bool isRenderable() const;
};

#endif
