#ifndef _SCENE_NODE_HPP
#define _SCENE_NODE_HPP

#include <string>
#include <map>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Node {
public:
    /**
     * Initializes a node.
     * @param name The name of the node.
     */
    Node(const std::string& name);

    /**
     * Adds a new child node. The child is being moved into the node.
     * @param node The new child.
     * @return A new valid pointer to the child.
     */
    Node* addChild(Node* node);

    /**
     * Returns a child node by its name.
     * @param name The child node name.
     * @return The child node, or nullptr if none found.
     */
    Node* getChild(const std::string& name);

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

private:
    std::map<std::string, std::unique_ptr<Node>> mChildren;
    Node* mParent = nullptr;
    std::string mName;

public:
    glm::vec3 position;
    glm::quat rotation;
};

#endif
