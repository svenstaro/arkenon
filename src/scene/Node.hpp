#ifndef _SCENE_NODE_HPP
#define _SCENE_NODE_HPP

#include <string>
#include <map>
#include <memory>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

class Node {
public:
    Node(const std::string& name);

    Node* addChild(Node* node);
    Node* getChild(const std::string& name);

    const std::string& getName();

    glm::vec3 getAbsolutePosition();
    glm::quat getAbsoluteRotation();
    glm::mat4 getTransformationMatrix();
    glm::mat4 getAbsoluteTransformationMatrix();

    void setAbsolutePosition(const glm::vec3& absolute_position);
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
