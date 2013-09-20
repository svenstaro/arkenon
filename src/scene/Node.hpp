#ifndef _SCENE_NODE_HPP
#define _SCENE_NODE_HPP

#include <string>
#include <map>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

#include "window/InputReceiver.hpp"
#include "render/Material.hpp"

class Node : public InputReceiver {
public:
    enum RenderTechnique {
        None,
        Deferred,
        Forward,
        Flat,
        LightBillboard,
        Default = Deferred,
        GUI = Flat
    };

public:
    /**
     * Initializes a node.
     * @param name The name of the node.
     */
    Node(const std::string& name, RenderTechnique render_technique = None);

    /**
     * Adds a new child node. The child is being moved into the node.
     * @param node The new child.
     * @return A new valid pointer to the child.
     */
    std::shared_ptr<Node> addChild(std::shared_ptr<Node> node);

    /**
     * Returns a child node by its name.
     * @param name The child node name.
     * @return The child node, or nullptr if none found.
     */
    std::shared_ptr<Node> getChild(const std::string& name);

    /**
     * Returns the name of this node.
     * @return  The node name.
     */
    const std::string& getName() const;

    /**
     * Returns the absolute position of this node.
     * @return The world space position.
     */
    glm::vec3 getAbsolutePosition() const;

    /**
     * Returns the absolute rotation of this node.
     * @return The world space rotation.
     */
    glm::quat getAbsoluteRotation() const;

    /**
     * Returns the absolute scale of this node.
     * @return The world space scale.
     */
    glm::vec3 getAbsoluteScale() const;

    /**
     * Calculates the local transformation matrix.
     * @return The parent-node space (local) transformation matrix.
     */
    glm::mat4 getTransformationMatrix() const;

    /**
     * Calculates the global transformation matrix.
     * @return The world space (global) transformation matrix.
     */
    glm::mat4 getAbsoluteTransformationMatrix() const;

    /**
     * Sets the absolute position of this node.
     * @param absolute_position The new world space position.
     */
    void setAbsolutePosition(const glm::vec3& absolute_position);

    /**
     * Sets the absolute rotation of this node.
     * @param absolute_rotation The new world space rotation.
     */
    void setAbsoluteRotation(const glm::quat& absolute_rotation);

    const Node* getParent() const;

    const std::map<std::string, std::shared_ptr<Node>>& getChildren() const;

    // render stuff
    virtual bool isVisible() const;
    virtual void onPrepareRender();
    virtual std::shared_ptr<Material> getMaterial();
    virtual glm::mat4 getModelMatrix() const;
    virtual void draw();

    void setRenderTechnique(RenderTechnique render_technique);
    RenderTechnique getRenderTechnique() const;

private:
    std::map<std::string, std::shared_ptr<Node>> mChildren;
    Node* mParent = nullptr;
    std::string mName;

protected:
    RenderTechnique mRenderTechnique;

public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
};

#endif
