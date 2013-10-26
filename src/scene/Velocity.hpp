#ifndef _SCENE_VELOCITY_HPP
#define _SCENE_VELOCITY_HPP

#include "scene/Node.hpp"
#include "window/Window.hpp"

class Velocity : public Node {
public:
    Velocity(const std::string& name);

    void onUpdate(double dt);

public:
    glm::vec3 linearVelocity;
    glm::vec3 angularVelocity;
    float linearDamping = 0.f;
    float angularDamping = 0.f;
    bool useLocalRotation = false;

};

#endif
